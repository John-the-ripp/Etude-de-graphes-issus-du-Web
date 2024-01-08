import pandas as pd
import matplotlib.pyplot as plt
import os


#C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\ il faut remplacé ce path avec celui qui contient les données
# de distribution
degree_dist_files = [
    "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\CA-GrQc.txt_degree_distribution.csv",
    "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\FacebookSites.csv_degree_distribution.csv",
    "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\Github.csv_degree_distribution.csv",
    "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\twitchDE.csv_degree_distribution.csv",
    "C:\\Users\\acer\\Desktop\\Anoussaa\\TEEEST\\Wikipedia1.csv_degree_distribution.csv"
]

x_axis_min = 0
x_axis_max = 130
for file in degree_dist_files:

    data = pd.read_csv(file, delimiter=";")

    degrees = data["Degree"]
    frequencies = data["Frequency"]

    plt.figure(figsize=(8, 6))
    plt.bar(degrees, frequencies, width=0.8, align="center")

    plt.xlim(x_axis_min, x_axis_max)

    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title(f"Degree Distribution for {os.path.basename(file)}")

    plt.grid(axis="y", linestyle="--", alpha=0.7)
    plt.show()
