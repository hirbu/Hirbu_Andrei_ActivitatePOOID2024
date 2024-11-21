#include <iostream>
#include <cstring>

class Autobuz {
private:
	static unsigned int nrAutobuze;
	unsigned const int idAutobuz;
	unsigned int capacitate;
	unsigned int nrPersoaneImbarcate;
	char* producator;

public:
	Autobuz() :idAutobuz(nrAutobuze++), capacitate(0), nrPersoaneImbarcate(0), producator(nullptr) {}

	Autobuz(unsigned const int capacitate, unsigned const int nrPersoaneImbarcate, const char* producator) :idAutobuz(nrAutobuze++), capacitate(capacitate), nrPersoaneImbarcate(nrPersoaneImbarcate), producator(nullptr)
	{
		if (this->capacitate < this->nrPersoaneImbarcate)
		{
			std::cout << "Eroare ID: " << this->idAutobuz << " | Numarul persoanelor imbarcate nu poate depasi capacitatea maxima a autobuzului.\n";
			return;
		}

		if (producator == nullptr)
		{
			std::cout << "Eroare ID: " << this->idAutobuz << " | Producatorul nu poate lipsi.\n";
			return;
		}
		size_t length = strlen(producator) + 1;
		this->producator = new char[length];
		strcpy_s(this->producator, length, producator);
	}

	Autobuz(const Autobuz& autobuz) :idAutobuz(nrAutobuze++), capacitate(autobuz.capacitate), nrPersoaneImbarcate(autobuz.nrPersoaneImbarcate), producator(nullptr)
	{
		if (autobuz.producator != nullptr)
		{
			size_t length = strlen(autobuz.producator) + 1;
			this->producator = new char[length];
			strcpy_s(this->producator, length, autobuz.producator);
		}
	}

	~Autobuz()
	{
		if (this->producator != nullptr)
		{
			delete[] this->producator;
		}
	}

	unsigned int getCapacitate() const
	{
		return this->capacitate;
	}

	void setCapacitate(unsigned const int capacitate)
	{
		this->capacitate = capacitate;
	}

	char* getProducator() const
	{
		return this->producator;
	}

	void setProducator(const char* producator)
	{
		if (producator == nullptr)
		{
			std::cout << "Eroare ID: " << this->idAutobuz << " | Producatorul nu poate fi nullptr.\n";
			return;
		}

		if (this->producator != nullptr)
		{
			delete[] this->producator;
		}
		size_t length = strlen(producator) + 1;
		this->producator = new char[length];
		strcpy_s(this->producator, length, producator);
	}

	Autobuz& operator=(const Autobuz& autobuz)
	{
		if (this == &autobuz)
		{
			return *this;
		}

		this->capacitate = autobuz.capacitate;

		this->nrPersoaneImbarcate = autobuz.nrPersoaneImbarcate;

		if (this->producator != nullptr)
		{
			delete[] this->producator;
		}
		size_t length = strlen(autobuz.producator) + 1;
		this->producator = new char[length];
		strcpy_s(this->producator, length, autobuz.producator);
	}

	friend std::ostream& operator<<(std::ostream& ostr, const Autobuz& autobuz);

	unsigned int getNumarLocuriLibere() const
	{
		unsigned const int numarLocuriLibere = this->capacitate - this->nrPersoaneImbarcate;

		return numarLocuriLibere;
	}

	operator int() const
	{
		return this->nrPersoaneImbarcate;
	}

	bool operator> (const Autobuz& autobuz) const
	{
		return this->capacitate > autobuz.capacitate;
	}
};

std::ostream& operator<<(std::ostream& ostr, const Autobuz& autobuz)
{
	ostr << autobuz.idAutobuz << "; " << autobuz.capacitate << "; " << autobuz.nrPersoaneImbarcate << "; ";

	if (autobuz.producator != nullptr)
	{
		ostr << autobuz.producator;
	}
	else
	{
		ostr << "NULL";
	}

	return ostr;
}

unsigned int Autobuz::nrAutobuze = 0;

int main()
{
	Autobuz autobuz1(31, 5, "Otokar");
	std::cout << "Autobuz 1				| " << autobuz1 << '\n';

	Autobuz autobuz2(autobuz1);
	std::cout << "Autobuz 2				| " << autobuz2 << '\n';

	autobuz1.setCapacitate(36);
	std::cout << "Autobuz 1 - Capacitate noua		| " << autobuz1.getCapacitate() << '\n';

	autobuz1.setProducator("Solaris");
	std::cout << "Autobuz 1 - Producator nou		| " << autobuz1.getProducator() << '\n';

	autobuz1 = autobuz2;
	std::cout << "Autobuz 1 - Atribuire autobuz 2		| " << autobuz1 << '\n';

	std::cout << "Autobuz 1 - Locuri libere		| " << autobuz1.getNumarLocuriLibere() << '\n';

	std::cout << "Autobuz 1 - Calatori imbarcati		| " << (int)autobuz1 << '\n';

	autobuz2.setCapacitate(15);
	if (autobuz1 > autobuz2)
	{
		std::cout << "Autobuzul 1 are o capacitate mai mare.\n";
	}
	else
	{
		std::cout << "Autobuzul 2 are o capacitate mai mare sau egala.\n";
	}

	return 0;
}
