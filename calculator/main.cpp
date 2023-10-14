#include <boost/program_options.hpp>
#include <iostream>
#include <vector>
#include <string>
namespace po = boost::program_options;
class Calculator {
private:
    po::options_description descr;
    po::positional_options_description p;
    po::variables_map vm;
    static constexpr size_t min = 3;
    static constexpr size_t max = 5;
    const std::string SUM = "plus";
    const std::string MINUS = "minus";
    int result = 0;
    std::vector<int> v;
    std::string action;
    void Input();
    void calculate();
public:
    Calculator() = delete;
    Calculator(int argc, char **argv);
    void print_result();
    int get_result() { return result; }
    void operator()();
};
Calculator::Calculator(int argc, char **argv) {
    descr.add_options()
        ("help", "Помощь")
        ("action", po::value<std::string>(&action), "выберете action: plus или minus")
        ("numb", po::value< std::vector<int> >(&v), "Введите числа от трех до пяти");
    p.add("numb", -1);
    po::store(po::command_line_parser(argc, argv).options(descr).positional(p).style(po::command_line_style::unix_style ^ po::command_line_style::allow_short).run(), vm);
    po::notify(vm);
}
void Calculator::operator()() {
    Input();
    calculate();
    print_result();
}
void Calculator::Input() {
    if ( vm.count("help") or vm.empty() ) {
        descr.print(std::cout);
        exit(1);
    }
//проверка на размер вектора
    if ( vm.count("numb") ) {
        if ( v.size() < min or v.size() > max ) {
            std::cerr << "Неверное количество входных данных" << std::endl;
            exit(1);
        }
    }
    //проверка на правильность написания
    if ( vm.count("action") ) {
        if ( action != SUM and action != MINUS ) {
            std::cerr << "Неверное имя действия" << std::endl;
            exit(1);
        }
    }
}
//функция для расчета суммы или вычитания из первого
void Calculator::calculate() {
    if ( action == SUM ) {
        for (int n : v)
            result += n;
    } else {
        result = v[0];
        for (size_t i=1;
             i<v.size();
             i++) 
             {
            result -= v[i];
        }
    }
}
void Calculator::print_result() {
    std::cout << "Результат: "
              << result
              << std::endl;
}
int main(int argc, char **argv) {
    Calculator calc(argc, argv);
    calc.get_result();
    calc();
}
//