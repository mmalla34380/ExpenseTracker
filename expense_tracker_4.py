import datetime

# List to store expenses as dictionaries
expenses = []

def add_expense():
    """Add a new expense to the list."""
    date_str = input("Enter date (YYYY-MM-DD): ")
    try:
        date = datetime.datetime.strptime(date_str, "%Y-%m-%d").date()
    except ValueError:
        print("Invalid date format. Please use YYYY-MM-DD.")
        return
    
    try:
        amount = float(input("Enter amount: "))
    except ValueError:
        print("Invalid amount. Please enter a number.")
        return
    
    category = input("Enter category: ")
    description = input("Enter description: ")
    
    expense = {
        'date': date,
        'amount': amount,
        'category': category,
        'description': description
    }
    expenses.append(expense)
    print("Expense added successfully.")

def view_expenses(filter_date_start=None, filter_date_end=None, filter_category=None):
    """View expenses with optional filters."""
    filtered = expenses[:]
    
    if filter_date_start:
        filtered = [e for e in filtered if e['date'] >= filter_date_start]
    if filter_date_end:
        filtered = [e for e in filtered if e['date'] <= filter_date_end]
    if filter_category:
        filtered = [e for e in filtered if e['category'].lower() == filter_category.lower()]
    
    if not filtered:
        print("No expenses found.")
        return
    
    print("\nExpenses:")
    for e in filtered:
        print(f"Date: {e['date']}, Amount: {e['amount']:.2f}, Category: {e['category']}, Description: {e['description']}")

def summary():
    """Calculate and display total expenses overall and by category."""
    if not expenses:
        print("No expenses to summarize.")
        return
    
    total = sum(e['amount'] for e in expenses)
    print(f"\nOverall Total: {total:.2f}")
    
    categories = {}
    for e in expenses:
        cat = e['category']
        categories[cat] = categories.get(cat, 0) + e['amount']
    
    print("Totals by Category:")
    for cat, amt in categories.items():
        print(f"{cat}: {amt:.2f}")

def main():
    """Main menu-driven loop."""
    while True:
        print("\nExpense Tracker Menu:")
        print("1. Add Expense")
        print("2. View All Expenses")
        print("3. Filter Expenses by Date Range")
        print("4. Filter Expenses by Category")
        print("5. View Summary")
        print("6. Exit")
        
        choice = input("Enter choice: ")
        
        if choice == '1':
            add_expense()
        elif choice == '2':
            view_expenses()
        elif choice == '3':
            start_str = input("Enter start date (YYYY-MM-DD): ")
            end_str = input("Enter end date (YYYY-MM-DD): ")
            try:
                start = datetime.datetime.strptime(start_str, "%Y-%m-%d").date()
                end = datetime.datetime.strptime(end_str, "%Y-%m-%d").date()
                view_expenses(filter_date_start=start, filter_date_end=end)
            except ValueError:
                print("Invalid date format.")
        elif choice == '4':
            category = input("Enter category: ")
            view_expenses(filter_category=category)
        elif choice == '5':
            summary()
        elif choice == '6':
            break
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()