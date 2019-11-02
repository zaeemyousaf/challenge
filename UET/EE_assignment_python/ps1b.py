#ps1b.py
annual_salary = int(input("Enter your starting annual salary: "))
portion_saved = float(input("Enter the percentage of your salary to save, as a decimal: "))
total_cost = int(input("Enter the cost of your dream home: "))
sami_annual_raise = float(input("Enter the sami annual raise, as a decimal: "))

#----------------- assumed values
current_savings = 0;
r = 0.04; # return rate per year
monthly_salary = annual_salary / 12.0;


portion_down_payment = 0.25; # assumed by question
down_payment = portion_down_payment* total_cost;


months=0; # month will increment in loop
while current_savings <= down_payment:
	current_savings = current_savings+ current_savings*(r)/12.0 + monthly_salary*portion_saved
	months=months+1
	if(months % 6 == 0):
		monthly_salary = monthly_salary * (1+sami_annual_raise)
		# for increase 1 is added

print("Number of Months: ", months)