#ps1a.py
annual_salary = int(input("Enter your annual salary: "))
portion_saved = float(input("Enter the percentage of your salary to save, as a decimal: "))
total_cost = int(input("Enter the cost of your dream home: "))

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

print("Number of Months: ", months)