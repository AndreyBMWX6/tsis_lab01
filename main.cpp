#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <map>
#include <utility>

const double t = 1.618034;

double get_func_val(double x) {
    return ((1 - x) * (1 - x) + std::exp(x));
}
void passive_search(double a, double b, double e) {
    std::cout << "Passive search:\n";
    int N = 0;
    double eps = (b - a) / N + 1;
    while (eps > e) {
        ++N;
        eps = (b - a) / (N + 1);
        std::map<double, double> func_values; // key -> f(x) | value -> x
        for (int k = 0; k < N; ++k) {
            double x = ((b - a) / (N + 1)) * k + a;
            func_values[get_func_val(x)] = x;
        }
        auto x = func_values.begin()->second;
        std::cout << "N = " << std::setw(2) << N << std::setw(7) <<
        "x = " << std::setw(8) << std::fixed << std::setprecision(5) << x << std::setw(4) << " +- " << eps << "\n";
    }
    return;
}


std::pair<double, double> golden_section_search_alg(double a, double b, double x1, double y1, double e) {
    if (b - a < e) {
        return std::make_pair(((a + b) / 2), e);
    } else {
        double x2 = a + b - x1;
        if (x2 < x1) {
            std::swap(x1, x2);
        }
        double y1 = get_func_val(x1);
        double y2 = get_func_val(x2);
        std::cout << "a = " << std::setw(8) << a << std::setw(8) << "b = " << std::setw(8) << b <<
        std::setw(8) << "l = " << std::setw(8) << b - a << std::setw(12) << "f(x1) = " << std::setw(8) <<
        std::setw(8) << y1 << std::setw(12) << "f(x2) = " << std::setw(8) << y2 << "\n";
        if (y1 < y2) {
            return golden_section_search_alg(a, x2, x1, y1, e);
        } else {
            return golden_section_search_alg(x1, b, x2, y2, e);
        }
    }
}

void golden_section_search(double a, double b, double e) {
    std::cout << "\nGolden search:\n";
    // 1 шаг золотого сечения
    std::pair<double, double> rez;
    double x1 = a + (1 - 1 / t) * b;
    double x2 = a + b / t;
    double y1 = get_func_val(x1);

    double y2 = get_func_val(x2);
    if (y1 < y2) {
        rez = golden_section_search_alg(a, x2, x1, y1, e);
    } else {
        rez = golden_section_search_alg(x1, b, x2, y2, e);
    }
    std::cout << "x = " << rez.first << " +- " << rez.second;
}

int main() {
    const double a = -4;
    const double b = 3;
    const double e = 0.1;

    passive_search(a, b, e);
    golden_section_search(a, b, e);
    return 0;
}
