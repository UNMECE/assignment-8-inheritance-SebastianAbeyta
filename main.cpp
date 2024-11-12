#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

const double k_e = 8.98755179e9;
const double mu_0 = 4 * M_PI * 1e-7;

class Field 
{
    protected:
    double *value;

    public:
        Field() 
        {
            value = new double[3];
            for (int i = 0; i < 3; ++i) 
            {
                value[i] = 0.0;
            }
        }

        Field(double x, double y, double z) 
        {
            value = new double[3];
            value[0] = x;
            value[1] = y;
            value[2] = z;
        }

        ~Field() 
        {
            delete[] value;
        }

        void printMagnitude() const 
        {
            cout << "Magnitude: (" << value[0] << ", " << value[1] << ", " << value[2] << ")" << endl;
        }
};

class Electric_Field : public Field 
{
    private:

        double electricField;

    public:
        double electricField;
        Electric_Field(double x, double y, double z) : Field(x, y, z) {}

        void calculateElectricField(double charge, double distance) 
        {
            electricField = k_e * charge / (distance * distance);
        }

        Electric_Field operator+(const Electric_Field& other) const 
        {
            Electric_Field result;
            for (int i = 0; i < 3; ++i) 
            {
                result.value[i] = value[i] + other.value[i];
            }
            return result;
        }

        friend ostream& operator<<(ostream& os, const Electric_Field& field) 
        {
            os << "Electric Field: (" << field.value[0] << ", " << field.value[1] << ", " << field.value[2] << ")" << endl;
            return os;
        }
};

class Magnetic_Field : public Field {
    private:
        double magneticField;

    public:
        Magnetic_Field(double x, double y, double z) : Field(x, y, z) {}

        void calculateMagneticField(double current, double distance) 
        {
            magneticField = mu_0 * current / (2 * M_PI * distance);
        }

        Magnetic_Field operator+(const Magnetic_Field& other) const 
        {
            Magnetic_Field result;
            for (int i = 0; i < 3; ++i) 
            {
                result.value[i] = value[i] + other.value[i];
            }
            return result;
        }

        friend ostream& operator<<(ostream& os, const Magnetic_Field& field) 
        {
            os << "Magnetic Field: (" << field.value[0] << ", " << field.value[1] << ", " << field.value[2] << ")" << endl;
            return os;
        }
};

int main() {
    Electric_Field e1(1, 2, 3), e2(4, 5, 6);
    Magnetic_Field b1(7, 8, 9), b2(10, 11, 12);

    e1.printMagnitude();
    b1.printMagnitude();

    e1.calculateElectricField(10, 2);
    b1.calculateMagneticField(5, 0.1);

    cout << "Electric Field: " << e1.electricField << endl;
    cout << "Magnetic Field: " << b1.magneticField << endl;

    Electric_Field e3 = e1 + e2;
    Magnetic_Field b3 = b1 + b2;

    cout << e3 << b3;

    return 0;
}
