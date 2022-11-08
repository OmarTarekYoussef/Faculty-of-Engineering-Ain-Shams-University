#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

const int si = 100;
double arr_nor[9][5];
double nor[9][5];
string s_data = "studentsData.csv";
string s_grade = "studentsGrade.csv";
string data[si][si];
string grade[si][si];
string removal(string s);
string gradesymbol();
void Read(string arr1[][si], string s);
void details();
double sd_math();
double sd_physics();
double sd_drawing();
double sd_computer();
double sd_chemistry();
void statistics();
void info(string s);
void Write(double arr_nor[9][5]);
void Write_symbol();
void Write_grades();
void Write_data();


class studentdata
{
protected:
    string code;
    string name;
    string age;
    string gender;

public:

    void set_code(string c)
    {
        code = c;
    }

    void set_name(string n)
    {
        name = n;
    }

    void set_age(string a)
    {
        age = a;
    }

    void set_gender(string g)
    {
        gender = g;
    }

    string get_code()
    {
        return code;
    }

    string get_name()
    {
        return name;
    }

    string get_age()
    {
        return age;
    }

    string get_gender()
    {
        return gender;
    }

};

class studentgrade
{
protected:
    string code;
    string math;
    string physics;
    string drawing;
    string computer;
    string chemistry;

public:

    void set_code(string c)
    {
        code = c;
    }

    void set_math(string m)
    {
        math = m;
    }

    void set_physics(string p)
    {
        physics = p;
    }

    void set_drawing(string d)
    {
        drawing = d;
    }

    void set_computer(string co)
    {
        computer = co;
    }

    void set_chemistry(string ch)
    {
        chemistry = ch;
    }

    string get_code()
    {
        return code;
    }

    double get_math()
    {
        stringstream geek(math);
        double x = 0;
        geek >> x;
        return x;
    }

    double get_physics()
    {
        stringstream geek(physics);
        double x = 0;
        geek >> x;
        return x;
    }

    double get_drawing()
    {
        stringstream geek(drawing);
        double x = 0;
        geek >> x;
        return x;
    }

    double get_computer()
    {
        stringstream geek(computer);
        double x = 0;
        geek >> x;
        return x;
    }

    double get_chemistry()
    {
        stringstream geek(chemistry);
        double x = 0;
        geek >> x;
        return x;
    }

};

studentdata students_data[si];
studentgrade students_grade[si];

int main()
{
    int x;
    string y;
    details();
    while(1)
    {
        cout << "Press 1 to export student data. "<< endl;
        cout << "Press 2 to export student grades. "<< endl;
        cout << "Press 3 to export normalize students results. "<< endl;
        cout << "Press 4 to export student grades symbols. "<< endl;
        cout << "Press 5 to get statistics for every grade band for each course. "<< endl;
        cout << "Press 6 to get student's basic information and grades. "<< endl;
        cout << "Press 7 to exit. "<< endl << endl;
        cout << "Enter your number: ";
        cin >> x;
        if(x == 1)
        {
            Write_data();
            cout << "Done, check your file location." << endl;
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;
        }
        else if(x == 2)
        {
            Write_grades();
            cout << "Done, check your file location." << endl;
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;
        }
        else if(x == 3)
        {
            Write(nor);
            cout << "Done, check your file location." << endl;
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;        }
        else if(x == 4)
        {
            Write_symbol();
            cout << "Done, check your file location." << endl;
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;
        }
        else if(x == 5)
        {
            statistics();
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;
        }
        else if(x == 6)
        {
            cout << "Please write the code of any student you want " << endl;
            cout << "Enter ID student: ";
            cin >> y;
            info(y);
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;
        }
        else if(x == 7)
        {
            cout << "--------------------------------" << endl;
            cout << "Thank you" << endl << endl;
            break;
        }
        else
        {
            cout << "Your number is not correct please try again. " << endl << endl;
            break;
        }
    }
}

void details()
{
    Read(data, s_data);
    Read(grade, s_grade);
    for(int i = 0 ; i <= 9; i++)
    {
        students_data[i].set_code(data[i][0]);
        students_data[i].set_name(data[i][1]);
        students_data[i].set_age(data[i][2]);
        students_data[i].set_gender(data[i][3]);

        students_grade[i].set_code(grade[i][0]);
        students_grade[i].set_math(grade[i][1]);
        students_grade[i].set_physics(grade[i][2]);
        students_grade[i].set_drawing(grade[i][3]);
        students_grade[i].set_computer(grade[i][4]);
        students_grade[i].set_chemistry(grade[i][5]);
    }
}


void Read(string arr1[][si], string s)
{
    ifstream data(s, ios::binary);
    string raw;
    int found = 0, j=0;
    if(data.is_open())
    {
        for(int i=0; !data.eof(); i++)
        {
            getline(data,raw);
            if(data.eof()) break;
            found = 0;
            j=0;
            while(found != -1)
            {
                for(int z =0; z < raw.length(); z++)
                {
                    if(raw[z] == ',')
                    {
                        found = z;
                        break;
                    }
                    else found = -1;
                    }
                    if(found != -1)
                    {
                        for(int f=0; f <found; f++)
                        {
                            arr1[i][j] += raw[f];
                        }
                        raw.erase(0, found +1);
                        j++;
                    }
                    else arr1[i][j] = raw;
            }
        }
        arr1[0][0] = removal(arr1[0][0]);
    }
    else
    {
            cout << "Can't open file" << endl;
    }
}


string removal(string s)
{
    string ns;
    for(int i = 3; i < s.length(); i++)
    {
        ns += s.at(i);
    }
    return ns;
}

double sd_math()
{
    double sum = 0.0, SD = 0.0, mean, res, o;
    for(int i = 1; i <= 9; i++)
    {
        sum += students_grade[i].get_math();
    }
    mean = sum / 9;
    for(int i = 1; i <= 9; i++)
    {
        SD += pow((students_grade[i].get_math() - mean), 2);
    }
    res = sqrt(SD / 9);
    for(int i = 1; i <= 9; i++)
    {
        o = (students_grade[i].get_math() - mean)/ res;
        arr_nor[i][1] = o;
    }
}

double sd_physics()
{
    double sum = 0.0, SD = 0.0, mean, res, o;
    for(int i = 1; i <= 9; i++)
    {
        sum += students_grade[i].get_physics();
    }
    mean = sum / 9;
    for(int i = 1; i <= 9; i++)
    {
        SD += pow((students_grade[i].get_physics() - mean), 2);
    }
    res = sqrt(SD / 9);
    for(int i = 1; i <= 9; i++)
    {
        o = (students_grade[i].get_physics() - mean)/ res;
        arr_nor[i][2] = o;
    }
}

double sd_drawing()
{
    double sum = 0.0, SD = 0.0, mean, res, o;
    for(int i = 1; i <= 9; i++)
    {
        sum += students_grade[i].get_drawing();
    }
    mean = sum / 9;
    for(int i = 1; i <= 9; i++)
    {
        SD += pow((students_grade[i].get_drawing() - mean), 2);
    }
    res = sqrt(SD / 9);
    for(int i = 1; i <= 9; i++)
    {
        o = (students_grade[i].get_drawing() - mean)/ res;
        arr_nor[i][3] = o;
    }
}

double sd_computer()
{
    double sum = 0.0, SD = 0.0, mean, res, o;
    for(int i = 1; i <= 9; i++)
    {
        sum += students_grade[i].get_computer();
    }
    mean = sum / 9;
    for(int i = 1; i <= 9; i++)
    {
        SD += pow((students_grade[i].get_computer() - mean), 2);
    }
    res = sqrt(SD / 9);
    for(int i = 1; i <= 9; i++)
    {
        o = (students_grade[i].get_computer() - mean)/ res;
        arr_nor[i][4] = o;
    }
}

double sd_chemistry()
{
    double sum = 0.0, SD = 0.0, mean, res, o;
    for(int i = 1; i <= 9; i++)
    {
        sum += students_grade[i].get_chemistry();
    }
    mean = sum / 9;
    for(int i = 1; i <= 9; i++)
    {
        SD += pow((students_grade[i].get_chemistry() - mean), 2);
    }
    res = sqrt(SD / 9);
    for(int i = 1; i <= 9; i++)
    {
        o = (students_grade[i].get_chemistry() - mean)/ res;
        arr_nor[i][5] = o;
    }
}

void Write(double nor[9][5])
{
    sd_math();
    sd_physics();
    sd_drawing();
    sd_computer();
    sd_chemistry();
    ofstream data_write("normalizedData.csv", ios::binary | ios::trunc);
    for(int i = 0; i <= 9; i++)
    {
        if(i == 0)
        {
            data_write <<
            "Student Code"<< ',' <<
            "Math" << ',' <<
            "Physics" << ',' <<
            "Drawing" << ',' <<
            "Computer" << ',' <<
            "Chemistry" << endl;
            continue;
        }
        for(int j = 0; j <= 5; j++)
        {
            switch(j)
            {
                case 0 :
                 data_write << students_grade[i].get_code() << ',';
                 break;
                default :
                 data_write << arr_nor[i][j] << ',';
                 break;
            }
            if(j == 5)
            {
                data_write << endl;
            }
        }
    }
    data_write.close();
}

string gradesymbol(double grade)
{
    if(grade >= 90)
    {
        return "A";
    }
    else if(grade < 90 && grade >= 85)
    {
        return "B+";
    }
    else if(grade < 85 && grade >= 80)
    {
        return "B";
    }
    else if(grade < 80 && grade >= 75)
    {
        return "C+";
    }
    else if(grade < 75 && grade >= 70)
    {
        return "C";
    }
    else if(grade < 70 && grade >= 65)
    {
        return "D+";
    }
    else if(grade < 65 && grade >= 60)
    {
        return "D";
    }
    else
    {
        return "F";
    }
}

void Write_symbol()
{
    ofstream data_write("GradesWithSymbols.csv", ios::binary | ios::trunc);
    for(int i = 0; i <= 9; i++)
    {
        if(i == 0)
        {
            data_write <<
            "Student Code"<< ',' <<
            "Math" << ',' <<
            "Physics" << ',' <<
            "Drawing" << ',' <<
            "Computer" << ',' <<
            "Chemistry" << endl;
            continue;
        }
        for(int j = 0; j <= 5; j++)
        {
            switch(j)
            {
                case 0 :
                data_write << students_grade[i].get_code() << ',';
                break;

                case 1 :
                data_write << gradesymbol(students_grade[i].get_math()) << ',';
                break;

                case 2 :
                data_write << gradesymbol(students_grade[i].get_physics()) << ',';
                break;

                case 3 :
                data_write << gradesymbol(students_grade[i].get_drawing()) << ',';
                break;

                case 4 :
                data_write << gradesymbol(students_grade[i].get_computer()) << ',';
                break;

                case 5 :
                data_write << gradesymbol(students_grade[i].get_chemistry()) << ','
                << endl;;
                break;
            }
        }
    }
    data_write.close();
}

void statistics()
{
    string arr_name[6] ={"First", "Math", "Physics", "Drawing", "Computer", "Chemistry"};
    int counter= 1;
    for(int i = 1; i <= 5; i++)
    {
        float A_st = 0.0, B1_st = 0.0, B_st = 0.0 ,C1_st = 0.0 ,C_st = 0.0 ,D1_st = 0.0 ,D_st = 0.0 ,F_st = 0.0;
        for(int j = 1; j <= 9; j++)
        {
            switch(counter)
            {
                case 1 :
                if(gradesymbol(students_grade[j].get_math()) == "A"){A_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "B+"){B1_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "B"){B_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "C+"){C1_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "C"){C_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "D+"){D1_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "D"){D_st ++;}
                if(gradesymbol(students_grade[j].get_math()) == "F"){F_st ++;}
                break;

                case 2 :
                if(gradesymbol(students_grade[j].get_physics())== "A"){A_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "B+"){B1_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "B"){B_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "C+"){C1_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "C"){C_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "D+"){D1_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "D"){D_st ++;}
                if(gradesymbol(students_grade[j].get_physics()) == "F"){F_st ++;}
                break;

                case 3 :
                if(gradesymbol(students_grade[j].get_drawing())== "A"){A_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "B+"){B1_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "B"){B_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "C+"){C1_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "C"){C_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "D+"){D1_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "D"){D_st ++;}
                if(gradesymbol(students_grade[j].get_drawing()) == "F"){F_st ++;}
                break;

                case 4 :
                if(gradesymbol(students_grade[j].get_computer())== "A"){A_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "B+"){B1_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "B"){B_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "C+"){C1_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "C"){C_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "D+"){D1_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "D"){D_st ++;}
                if(gradesymbol(students_grade[j].get_computer()) == "F"){F_st ++;}
                break;

                case 5 :
                if(gradesymbol(students_grade[j].get_chemistry())== "A"){A_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "B+"){B1_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "B"){B_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "C+"){C1_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "C"){C_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "D+"){D1_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "D"){D_st ++;}
                if(gradesymbol(students_grade[j].get_chemistry()) == "F"){F_st ++;}
                break;
            }
        }
        counter++;
        cout << "in " << arr_name[i] << " course: " << (A_st / 9)*100 << "% of the students got A" << endl;
        cout << "in " << arr_name[i] << " course: " << (B1_st / 9)*100 << "% of the students got B+" << endl;
        cout << "in " << arr_name[i] << " course: " << (B_st / 9)*100 << "% of the students got B" << endl;
        cout << "in " << arr_name[i] << " course: " << (C1_st / 9)*100 << "% of the students got C+" << endl;
        cout << "in " << arr_name[i] << " course: " << (C_st / 9)*100 << "% of the students got C" << endl;
        cout << "in " << arr_name[i] << " course: " << (D1_st / 9)*100 << "% of the students got D+" << endl;
        cout << "in " << arr_name[i] << " course: " << (D_st / 9)*100 << "% of the students got D" << endl;
        cout << "in " << arr_name[i] << " course: " << (F_st / 9)*100 << "% of the students got F" << endl;
        cout << endl;

    }
}

void info(string s)
{
    int flag = 0;
    for(int i = 1; i <= 10; i++)
    {
        if(s == students_grade[i].get_code())
        {
            flag = 1;
            cout << "Code: " << students_data[i].get_code() << endl;
            cout << "Name: " << students_data[i].get_name() << endl;
            cout << "Age: " << students_data[i].get_age() << " years old" <<endl;
            cout << "Gender: " << students_data[i].get_gender() << endl;
            cout << "Math degree = " << students_grade[i].get_math() << endl;
            cout << "Physics degree = " << students_grade[i].get_physics() << endl;
            cout << "Drawing degree = " << students_grade[i].get_drawing() << endl;
            cout << "Computer degree = " << students_grade[i].get_computer() << endl;
            cout << "Chemistry degree = " << students_grade[i].get_chemistry() << endl;
        }
    }
    if(flag == 0)
    {
        string y;
        cout << "ID student is not correct. " << endl;
        cout << "Enter ID student: ";
        cin >> y;
        info(y);
    }
}

void Write_grades()
{
    ofstream data_write("students_Grade_OUTPUT.csv", ios::binary | ios::trunc);
    for(int i = 0; i <= 9; i++)
    {
        if(i == 0)
        {
            data_write <<
            "Student Code"<< ',' <<
            "Math" << ',' <<
            "Physics" << ',' <<
            "Drawing" << ',' <<
            "Computer" << ',' <<
            "Chemistry" << endl;
            continue;
        }
        for(int j = 0; j <= 5; j++)
        {
            switch(j)
            {
                case 0 :
                data_write << students_grade[i].get_code() << ',';
                break;

                case 1 :
                data_write << students_grade[i].get_math() << ',';
                break;

                case 2 :
                data_write << students_grade[i].get_physics() << ',';
                break;

                case 3 :
                data_write << students_grade[i].get_drawing() << ',';
                break;

                case 4 :
                data_write << students_grade[i].get_computer() << ',';
                break;

                case 5 :
                data_write << students_grade[i].get_chemistry() << ','
                << endl;;
                break;
            }
        }
    }
    data_write.close();
}

void Write_data()
{
    ofstream data_write("students_Data_OUTPUT.csv", ios::binary | ios::trunc);
    for(int i = 0; i <= 9; i++)
    {
        if(i == 0)
        {
            data_write <<
            "Code"<< ',' <<
            "Name" << ',' <<
            "Age" << ',' <<
            "Gender" << endl;
            continue;
        }
        for(int j = 0; j <= 3; j++)
        {
            switch(j)
            {
                case 0 :
                data_write << students_data[j].get_code() << ',';
                break;

                case 1 :
                data_write << students_data[j].get_name() << ',';
                break;

                case 2 :
                data_write << students_data[j].get_age() << ',';
                break;

                case 3 :
                data_write << students_data[j].get_gender() << ','
                << endl;;
                break;
            }
        }
    }
    data_write.close();
}
