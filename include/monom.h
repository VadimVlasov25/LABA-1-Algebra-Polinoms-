// класс или структура Монома (double коэффициент, целая свернутая степень)
#ifndef __MONOM_H__
#define __MONOM_H__
class Monom
{
private:
	double factor;
	int power;
public:
	Monom(double factor_new = 0, int pow_x = 0, int pow_y = 0, int pow_z = 0);
	Monom(Monom& m2);
	~Monom();
	double GetFactor() { return factor; };
	void SetFactor(double factor_new) { factor = factor_new; };
	int GetPower() { return power; };
	void SetPower(int pow_x, int pow_y, int pow_z);
	Monom& operator=(Monom& m2);

};
#endif