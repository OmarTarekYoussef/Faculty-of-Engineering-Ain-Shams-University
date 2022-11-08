# Computer Programming
 
One of the functions of the Learning Management System (LMS) is to provide
teachers with tools to view and analyze students’ grades. The aim of this exercise
is to import students’ data and perform some statistical operations such as
normalization and transform them into symbol grades representation. The
program should have a menu of the following functions:
• Import/export student data...
• Import/export student grade
• Modify grades:
o Normalize
o export GPA grades

The implementation of the project can be done in following parts:
Part 1:
The file “studentsData.csv” contains the data of the students represented as
columns. Use this file to create an array that holds the students’ information (ID,
Name, Age, Gender, etc..). You can either represent the data as a
Multidimensional array or an Array of Objects (of course you would first have to
create the Student Class first).

Part 2:
The file “studentsGrades.csv” contains the student’s grades for five different
courses. All the grades are marked out of 100. Write a function to normalize the
results of each course. The function takes the raw data as input, calculates the
mean and standard deviation and then computes the normalized data. Use the
following equations to normalize the data:
o =
x−μ
σ
where:
μ: is the mean of the grades in the course
σ: Standard deviation of the grades

Part 3:
Replace the students’ grades with grades symbols according to the following
table:
Range Symbol
≥ 90 A
90 < 85 B+
80 < 85 B
75 < 80 C+
70 < 75 C
65 < 70 D+
60 < 65 D
60 F
Then export the modified data to a CSV file.
Part 4:
Write a function that provides statistics for every grade band for each course. For
example, in the Maths(1) course: 10% of the students got A, 20% got B, 40% got C
and so on.
Part 5:
Write a function that prints a student’s basic information and grades given the
student’s ID.

Sample data to try your program on is found in this link