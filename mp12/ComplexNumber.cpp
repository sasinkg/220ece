#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    /*  code here */
    real_component = 0;
    magnitude = 0;
    phase = 0;
    number_type = COMPLEX;
   
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    /* Your code here */
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
    magnitude = sqrt((rval_real_component*rval_real_component)+(rval_imaginary_component*rval_imaginary_component));
    phase = calculate_phase(real_component,imaginary_component)
    //calculate_phase = atan(imaginary_component/real_component);
    number_type = COMPLEX;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    /* Your code here */
}

void ComplexNumber::set_real_component (double rval)
{
    /* Your code here */
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return 0.0;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return 0.0;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return 0.0;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return 0.0;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component + arg.real_component, imaginary_component + arg.imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.real_component, imaginary_component - arg.imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    // double realReal = real_component * arg.real_component;
    // double imaginaryImaginary = -1*imaginary_component * arg.imaginary_component
    // double realImaginary = real_component*arg.imaginary_component;
    // double imaginaryReal = imaginary_component*arg.real_component;
    // double real = realReal + imaginaryImaginary;
    // double imaginary = realImaginary + imaginaryReal;
    // return ComplexNumber(real, imaginary);
    
    return ComplexNumber(((real_component * arg.real_component)+(-1*imaginary_component * arg.imaginary_component)), ((real_component * arg.imaginary_component) + (imaginary_component * arg.real_component)));
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    double mag = arg.get.magnitude();
    return ComplexNumber((((real_component * arg.real_component)+(-1*imaginary_component * arg.imaginary_component))/(mag*mag)), (((real_component * arg.imaginary_component) - (imaginary_component * arg.real_component))/(mag*mag)));
}
// (a,b) + c = (a+c, b)
ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component + arg.get_real_component, imaginary_component + 0);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component - arg.get_real_component, imaginary_component - 0);
}
// (a,b) * c = (ac, cb)
ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component * arg.get_real_component, imaginary_component * arg.get_real_component);
}
// (a,b) / c = (a/c, b/c)
ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component / arg.get_real_component, imaginary_component / arg.get_real_component);
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component + 0, imaginary_component + arg.get_imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component - 0, imaginary_component - arg.get_imaginary_component);
}
// (a,b) * ci = (i^2*bc, a*ci)
ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(imaginary_component * arg.get_imaginary_component, real_component * arg.get_imaginary_component);
}
// (a,b) / ci = ()
ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(imaginary_component / arg.get_imaginary_component, real_component / arg.get_imaginary_component);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}