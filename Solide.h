class Solide
{
private:
	int largeur;
	float couplageJ;
	float champB;
	float momentMag;
	float temperature;	//= thermostat puisque le système est à l'équilibre. (ensemble canonique)

public:
	virtual ~Solide();
};
