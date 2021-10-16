# Datascience X Logistic Regression (DSLR)
'''html
**NOTE:**<span style="color:red">The project is still ongoing. Daily updates into the contents.</span>
'''
## 1. Project overview

The project is part of my studying at [Hive (Helsinki) Coding School](https://hive.fi). Programs are written in C-, and python- languages. An additional visualization (Bonus part of the project) I used Influxdb and Grafana which are running inside a docker container. For learning and testing purposes I used a Jupyter notebook. The picture below visualizes a general overview of projects at Hive (Helsinki) Coding School.

![Hive_Holy_Graph](Documentation/Hive_Holy_Graph.png)

## 2. Project description

**Note.** Text into this chapter (project description) was copied (partly or fully) from Hive Coding School document.

### 2.1 Introduction

On no! Since its creation, the famous school of wizards, Hogwarts, had never known such an offense. The forces of evil have bewitched the Sorting Hat. It no longer responds, and is unable to fulfill his role of sorting the students to the houses. The new academic year is approaching. Gladly, the Professor McGonagall was able to take action in such a stressful situation, since it is impossible for Hogwarts not to welcome new students. . . She decided to call on you, a muggle "datascientist" who is able to create miracles with the tool which all muggles know how to use: a "computer". Despite the intrinsic reluctance of many wizards, the director of the school welcomes you to his office to explain the situation. You are here because his informant discovered that you are able to recreate a magic Sorting Hat using your muggle tools. You explain to him that in order for your "muggle" tools to work, you need students data. Hesitantly, Professor McGonagall gives you a dusty spellbook. Fortunately for you, a simple "Digitalis!" and the book turned into a USB stick.

### 2.2 Objectives

In this project DataScience x Logistic Regression, you will continue your exploration of Machine Learning by discovering different tools. The use of the term DataScience in the title will be clearly considered by some to be abusive. That is true. We do not pretend to give you all the basics of DataScience in this topic. The subject is vast. We will only see here some bases which seemed to us useful for data exploration before sending it to the machine learning algorithm . You will implement a linear classification model, as a continuation of the subject linear regression : a logistic regression. We also encourage you a lot to create a machine learning toolkit while you will move along the branch.

**Summarizing**
- You will learn how to read a data set, to visualize it in different ways, to select and clean unnecessary information from your data.
- You will train a logistic regression that will solve classification problem.

### 2.3 Formulas for calculation

![sigmoid](https://latex.codecogs.com/svg.latex?\Large&space;sigmoid(z)=\frac{1}{1+e^{-z})

![Cost](https://latex.codecogs.com/svg.latex?\Large&space;J(\theta)=-\frac{1}{m}\sum_{i=1}^{m}y^ilog(h_\theta(x^i))+(1-y^i)log(1-h_\theta(x^i)))

## 5. Solution

### 5.1 Solution overview

### 5.2 Visualization

#### 5.2.1 Describe

![Describe](Documentation/Python_Describe.png)

#### 5.2.2 Box plot

Boxplot visualizes functions (values of them) so that it's easy to get an overview of functions. In the picture below we see that some functions include values that are not within common (Q1 and Q3) limits. To avoid unexpected behavior during data processing the content of those functions requires deeper analysis.

![Boxplot](Documentation/Python_Boxplot.png)

#### 5.2.3 Correlations plot

Correction plot visualizes correlation between functions. Functions that correlate strongly do not add additional value for data processing. In case of limitation of the amount of input data is required, selecting just one of the functions that correlate each other might be a valid solution. The correlation could be the same or opposite direction. In the picture below the yellow and the purple colors indicate a strong correlation between functions.

![Correlationsplot](Documentation/Python_Correlationsplot.png)

#### 5.2.4 Histogram plot

Histogram plots visualize how values in a function are distributed. Currently, I do not have any idea how this information could be useful for data processing. Let see do I get some ideas in the future.

![Histogramsplot](Documentation/Python_Histogramplot.png)

#### 5.2.5 Scatter plot

A scatter plot and correlation plot visualizes similar things (at least from my point of view). The visualization view is different that makes the possibility for a different kind of information. Currently, I don't know what kind of, but in any case.

![Scatterplot](Documentation/Python_Scatterplot.png)

### 5.3 Implemented Matrix and Vector calculation funtions

To learn (all details) I decided to write logistic regression functionality with C-language. It's a lot of work and forces me to really understand how details must be implemented. Looking forward that this kind of way of learning helps me to use ready-made functionality (like in numpy, pandas etc...) fluently.
Below, is a list of matrix/vector functions that I wrote.

| Name of the function | similar functionality in python
|:-|:-|
| ft_double_div_vector.c | [numpy.divide](https://numpy.org/doc/stable/reference/generated/numpy.divide.html?highlight=div#numpy.divide) |
| ft_double_subtract_matrix.c | [numpy.subtract](https://numpy.org/doc/stable/reference/generated/numpy.subtract.html?highlight=subtract) |
| ft_matrix_add_double.c | [numpy.add](https://numpy.org/doc/stable/reference/generated/numpy.add.html?highlight=add#numpy.add) |
| ft_matrix_add_matrix.c | [numpy.add](https://numpy.org/doc/stable/reference/generated/numpy.add.html?highlight=add#numpy.add) |
| ft_matrix_add_vector.c | [numpy.add](https://numpy.org/doc/stable/reference/generated/numpy.add.html?highlight=add#numpy.add) |
| ft_matrix_div_vector.c | [numpy.divide](https://numpy.org/doc/stable/reference/generated/numpy.divide.html?highlight=div#numpy.divide) |
| ft_matrix_dot_matrix.c | [nympy.dot](https://numpy.org/doc/stable/reference/generated/numpy.dot.html) |
| ft_matrix_dot_vector_double.c | [nympy.dot](https://numpy.org/doc/stable/reference/generated/numpy.dot.html) |
| ft_matrix_exp_double.c | [numpy.exp](https://numpy.org/doc/stable/reference/generated/numpy.exp.html) |
| ft_matrix_log.c | [numpy.log](https://numpy.org/doc/stable/reference/generated/numpy.log.html) |
| ft_matrix_max.c | [numpy.matrix.max](https://numpy.org/doc/stable/reference/generated/numpy.matrix.max.html?highlight=max#numpy.matrix.max) |
| ft_matrix_min.c | [numpy.matrix.min](https://numpy.org/doc/stable/reference/generated/numpy.matrix.min.html?highlight=min#numpy.matrix.min) |
| ft_matrix_multiply_matrix.c | [numpy.multiply](https://numpy.org/doc/stable/reference/generated/numpy.multiply.html) |
| ft_matrix_subtract_matrix.c | [numpy.subtract](https://numpy.org/doc/stable/reference/generated/numpy.subtract.html?highlight=subtract) |
| ft_matrix_subtract_vector.c | [numpy.subtract](https://numpy.org/doc/stable/reference/generated/numpy.subtract.html?highlight=subtract) |
| ft_matrix_sum.c | [numpy.sum](https://numpy.org/doc/stable/reference/generated/numpy.sum.html) |
| ft_matrix_transpose.c | [numpy.transpose](https://numpy.org/doc/stable/reference/generated/numpy.transpose.html?highlight=transpose#numpy.transpose) |
| ft_vector_abs_double.c | [numpy.absolute](https://numpy.org/doc/stable/reference/generated/numpy.absolute.html?highlight=abs#numpy.absolute) |
| ft_vector_add_double.c | [numpy.add](https://numpy.org/doc/stable/reference/generated/numpy.add.html?highlight=add#numpy.add) |
| ft_vector_add_vector.c | [numpy.add](https://numpy.org/doc/stable/reference/generated/numpy.add.html?highlight=add#numpy.add) |
| ft_vector_div_double.c | [numpy.divide](https://numpy.org/doc/stable/reference/generated/numpy.divide.html?highlight=div#numpy.divide) |
| ft_vector_transpose.c | [numpy.transpose](https://numpy.org/doc/stable/reference/generated/numpy.transpose.html?highlight=transpose#numpy.transpose) |

### 5.4 Implemented activation functions

### 5.5 Implemented gradient descent functions

### 5.6 Implemented command line arguments

#### 5.6.1 Optional arguments

| Argument | Description |
| :-: | - |
| -A \<learning rate\> | Learning rate for gradient descent calculations (backward propagation) |
| -I \<number of itetation loops\> | Number of iteration loops |
| -S | Send (statistical) data to influx database |
| -h | Help printout |
| -l | Print leaks, if any. Only in MAC-OS |

#### 5.6.2 Mandatory arguments

| Argument | Description |
| :- | - |
| \<mode\> | The mode specify contnet of an input file.<br>TRAIN --> Training examples<br>TEXT --> Test examples|
| \<input_file\> | A file includes either learning or test examples |
