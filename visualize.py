import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("dataset/fake_bills.csv", delimiter=';')

# Get the count of genuine and fake bills
genuine_bills = data[data['is_genuine'] == True].shape[0]
fake_bills = data[data['is_genuine'] == False].shape[0]

# Create a pie chart with the count of genuine and fake bills
pie_chart_data = [genuine_bills, fake_bills]
pie_chart_labels = ['Genuine', 'Fake']
plt.pie(pie_chart_data, labels=pie_chart_labels, autopct="%1.1f%%")
plt.title('Distribution of Genuine and Fake Bills')
plt.show()
