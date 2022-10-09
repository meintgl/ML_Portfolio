# ML_Portfolio

## Overview of Machine Learning

This document serves as in introduction to Machine Learning, and marks the beginning of my exploration in this particular field. It defines key terms in machine learning and touches on my personal interest in taking Machine Learning and potential applications to projects I have.

You can read the [document here](ml_overview.pdf).

## Data Exploration

This is the first project from Machine Learning class, which uses C++ to explore data read from a .csv files. The csv file has 2 columns with float values, and the program puts them into 2 double vectors. There are six functions implemented, which are the sum, mean, median, range, covariance, and colleration. The first four are called separately for the two vectors, and the covariance and correlation is called for both vectors together. The results of the function are printed at the end of the program.

You can read the [document here](https://github.com/meintgl/ML_Portfolio/blob/main/Data%20Exploration/dataExploration.pdf) and look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/Data%20Exploration/dataExploration.cpp).

## Linear Models
This project explores regression and classification. Regression is done with a dataset containing information on diamonds, where different variables are explored to predict a diamond's price. A linear regression model with different predictors is created to facilitate this.

You can read the [PDF document here](https://github.com/meintgl/ML_Portfolio/blob/main/Linear%20Model%20Project/Regression.pdf) and look at the [markdown code here](https://github.com/meintgl/ML_Portfolio/blob/main/Linear%20Model%20Project/Regression.Rmd).

For the second part, classification is done with a dataset containning customer satisifcation on airlines based on different factors. Different variables are explored to predict whether a customer is "satisfied" or "dissatisfied". Logistic regression and the Naive Bayes model is created to facilitate this.

You can read the [PDF document here](https://github.com/meintgl/ML_Portfolio/blob/main/Linear%20Model%20Project/Classification.pdf) and look at the [markdown code here](https://github.com/meintgl/ML_Portfolio/blob/main/Linear%20Model%20Project/Classification.Rmd).

**Datasets (Direct Download)**

[Diamond Dataset](https://github.com/meintgl/ML_Portfolio/blob/main/Linear%20Model%20Project/diamonds.csv)

[Airline Dataset](https://github.com/meintgl/ML_Portfolio/blob/main/Linear%20Model%20Project/Invistico_Airline.csv)


## ML Algorithms from Scratch
This project implements the equations and math required to calculate logistic regression and naive bayes model in C++. The titanic dataset is used for data.

For logistic regression, passenger survival is predicted with sex as a sole factor. The accuracy of the model turned out to be arond 78.1%.

You can look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/ML%20Algorithms%20from%20Scratch/logisticRegression.cpp).

For naive bayes, passenger survival is predicted with sex, age, and passenger class as factors. The accuracy of the model turned out to be arond 78.5%, slightly higher than our logistic regression mode.

You can look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/ML%20Algorithms%20from%20Scratch/naiveBayes.cpp).

For analysis on both models and our data, feel free to read the [PDF document here](https://github.com/meintgl/ML_Portfolio/blob/main/ML%20Algorithms%20from%20Scratch/ML%20Algorithms%20from%20Scratch.pdf).

**Datasets (Direct Download)**

[Titanic Dataset](https://github.com/meintgl/ML_Portfolio/blob/main/ML%20Algorithms%20from%20Scratch/titanic_project.csv)

## Searching for Similarity

This project implements four notebooks to showcase similarity models, clustering methods, and dimensionality reeduction techniques.

Notebook 1 deals with regression, specifically: linear regression, kNN regression and Decision tree regression.

You can look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Regression.Rmd) and read the [PDF Document here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Regression.pdf).

Notebook 2 deals with classification, Logistic Regression, kNN, and Decision Trees.

You can look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Classification.Rmd) and read the [PDF Document here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/pfc4_Classification.pdf).

Notebook 3 deals with kNN clustering, hierarchical clustering, and model based clustering.

You can look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Clustering.Rmd) and read the [PDF Document here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Clustering.pdf).

Notebook 4 deals with dimensionality reduction

You can look at the [code here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Dimensionality_Reduction.Rmd) and read the [PDF Document here](https://github.com/meintgl/ML_Portfolio/blob/main/Searching%20by%20Similarity/Dimensionality_Reduction.pdf).
