#ps1c.py
annual_salary = int(input("Enter the starting salary: "))
total_cost = 1000000
sami_annual_raise = .07; # given
#----------------- assumed values
current_savings = 0;
r = 0.04; # return rate per year
monthly_salary = annual_salary / 12.0;


portion_down_payment = 0.25; # assumed by question
down_payment = portion_down_payment* total_cost;


months=1; # month will increment in loop
sum_of_salary = 0
bisection_search=0;
while months <= 36:
	sum_of_salary = sum_of_salary + monthly_salary;
	if (bisection_search ==0 and sum_of_salary > down_payment):
		bisection_search=months;
	months=months+1
	if(months % 6 == 0):
		monthly_salary = monthly_salary * (1+sami_annual_raise)
		# for increase 1 is added
if(sum_of_salary > down_payment):
	best_rate=(down_payment/float(sum_of_salary))-0.15
	print("best saving rate: {0:.2} ".format(best_rate))
	print("Steps in bisection search: ",bisection_search)

else:
	print("it is not possible to pay the down payment in three years.")
