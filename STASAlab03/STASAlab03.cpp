#include <iostream>
#include <cmath>
#include <iomanip>

// lab03 
// simulated annealing

// task data zone ------------------------
static const int left = -4;
static const int right = 3;

double main_function_1(double x)
{
	return pow(1 - x, 2) + exp(x);
}

double main_function_2(double x)
{
	return (pow(1 - x, 2) + exp(x)) * sin(5 * x);
}
// end task data zone ---------------------

double cool_off(double& curr_temp)
{
	curr_temp = 0.95 * curr_temp;
	return curr_temp;
}

// Функция, генерирующая случайное действительное число от left до right
double random_double(const double& left, const double& right)
{
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * abs((right - left)) + left;
}

double varranity_of_change(const double& value_difference, const double& temperature)
{
	if (value_difference < 0) return 1;
	else return exp(value_difference / temperature);
}

bool is_there_change(const double& value_difference, const double& temperature)
{
	double change_varranity = varranity_of_change(value_difference, temperature);
	if (change_varranity == 1) return true;
	else {
		double tmp = random_double(0, 1);
		if (tmp < change_varranity) return true;
		else return false;
	}
}

void find_min(double(*math_function)(double))
{
	const double start_temperature = 10000;
	const double end_temperature = 0.1;

	double current_temperature = start_temperature;

	double current_x = random_double(left, right);
	double func_value = math_function(current_x);

	double minimum = func_value;
	int iteration = 1;
	std::cout << std::setprecision(3);
	double new_x = current_x;
	while (current_temperature > end_temperature) {
		std::cout << iteration << ' ' << current_temperature << ' ' << current_x
			<< ' ' << math_function(new_x) - math_function(current_x) << std::endl;
		double new_x = random_double(current_x - 0.3, current_x + 0.3);
		if (is_there_change(math_function(new_x)-math_function(current_x), current_temperature)) {
			current_x = new_x;
			if (math_function(current_x) < minimum) {
				minimum = math_function(current_x);
			}
		}
		current_temperature = cool_off(current_temperature);
		iteration++;
	}
	std::cout << "minimum is " << minimum << std::endl;
}

int main()
{
	// for (int i = 0; i < 100; i++) std::cout << random_double(left, right) << std::endl;
	srand(time(NULL));
	find_min(main_function_1);
	std::cout << "_________________" << std::endl;
	find_min(main_function_2);
}
