#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <regex>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;
char* AlocirajTekst(const char* tekst) {
	if (!tekst) return nullptr;
	size_t vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}

string crt = "\n-------------------------------------------------------------------------------- - \n";

string PORUKA_TELEFON = crt +
"TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n"
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO." + crt;

string PORUKA_ISPIT = crt +
"0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN DESTRUKTOR\n"
"2. IZOSTAVLJANJE DESTRUKTORA ILI NJEGOVIH DIJELOVA BIT CE OZNACENO KAO TM\n"
"3. ATRIBUTI, METODE I PARAMETRI MORAJU BITI IDENTICNI ONIMA U TESTNOJ MAIN FUNKCIJI, "
" OSIM AKO POSTOJI JASAN RAZLOG ZA MODIFIKACIJU\n"
"4. IZUZETKE BACAJTE SAMO TAMO GDJE JE IZRICITO NAGLASENO\n"
"5. SVE METODE KOJE SE POZIVAJU U MAIN-U MORAJU POSTOJATI.\n"
" AKO NEMATE ZELJENU IMPLEMENTACIJU, OSTAVITE PRAZNO TIJELO ILI VRATITE NEKU DEFAULT VRIJEDNOST\n"
"6. RJESENJE KOPIRAJTE U .DOCX DOKUMENT (NAZIV DOKUMENTA = BROJ INDEKSA, npr.IB150051.docx)\n"
"7. NA FTP SERVER POSTAVITE SAMO .DOCX DOKUMENT, A NE CIJELI PROJEKAT\n"
"8. SVE NEDOZVOLJENE RADNJE TOKOM ISPITA BIT CE SANKCIONISANE\n"
"9. U MAIN FUNKCIJI MOZETE DODAVATI TESTNE PODATKE I POZIVE PO VLASTITOM IZBORU\n"
"10. KORISTITE VISUAL STUDIO 2022 (C++17) I TESTIRAJTE PROGRAM U OBA MODA(F5 i Ctrl + F5)\n"
"11. NA KRAJU PROVJERITE DA LI STE RJESENJE ISPITA POSTAVILI U ODGOVARAJUCI FOLDER NA FTP SERVERU" + crt;

enum Kategorija { ELEKTRONIKA, KNJIGE, MODA, PREHRANA };
const char* KategorijaNazivi[] = { "ELEKTRONIKA", "KNJIGE", "MODA", "PREHRANA" };
ostream& operator<<(ostream& COUT, const Kategorija& kategorija) {
	switch (kategorija)
	{
	case 0:
		COUT << "ELEKTRONIKA";
		break;
	case 1:
		COUT << "KNJIGE";
		break;
	case 2:
		COUT << "MODA";
		break;
	case 3:
		COUT << "PREHRANA";
		break;
	default:
		COUT << "Kategorija nije pronadjena!";
		break;
	}
	return COUT;
}
int getCurrentYearBySystem() {
	time_t trenutnoVrijeme = time(nullptr);
	tm lokalnoVrijeme{};
	localtime_s(&lokalnoVrijeme, &trenutnoVrijeme);
	return lokalnoVrijeme.tm_year + 1900;
}
string GenerisiSifru(const char* imePrezime, int broj) {

	int godina = getCurrentYearBySystem();
	string GodinaStr = to_string(godina);
	string BrojStr = to_string(broj);
	string ImePrezimeStr = imePrezime;
	string Sifra{};

	size_t pozicijaPrezimena = ImePrezimeStr.find(' ') + 1;

	Sifra += imePrezime[0];
	Sifra += imePrezime[pozicijaPrezimena];
	Sifra += ':';
	Sifra += GodinaStr;
	Sifra += '-';
	if (broj < 10) {
		Sifra += "00";
	}
	else if (broj < 100) {
		Sifra += '0';
	}
	Sifra += BrojStr;

	return Sifra;
}
bool ValidirajSifru(string sifra) {
	return regex_match(sifra, regex("[A-Z]{2}[:]{1}[\\d]{4}[-]{1}[\\d]{3}"));
}
template<class T1, class T2, int max>
class KolekcijaParova {
	T1* _prvi[max] = { nullptr };
	T2* _drugi[max] = { nullptr };
	int _trenutno = 0;
public:
	KolekcijaParova() = default;
	KolekcijaParova(const KolekcijaParova& obj)
	{
		_trenutno = obj.GetTrenutno();
		for (int i = 0; i < GetTrenutno(); i++) {
			_prvi[i] = new T1{ obj.GetPrvi(i) };
			_drugi[i] = new T2{ obj.GetDrugi(i) };
		}
	}
	KolekcijaParova& operator=(const KolekcijaParova& obj) {
		if (this == &obj) {
			return *this;
		}
		dealocirajElemente();
		_trenutno = obj.GetTrenutno();
		for (int i = 0; i < GetTrenutno(); i++) {
			_prvi[i] = new T1{ obj.GetPrvi(i) };
			_drugi[i] = new T2{ obj.GetDrugi(i) };
		}
		return *this;
	}
	~KolekcijaParova() {
		dealocirajElemente();
	}
	int GetTrenutno() const { return _trenutno; }
	const T1& GetPrvi(int indeks) const { return *_prvi[indeks]; }
	T1& GetPrvi(int indeks) { return *_prvi[indeks]; }
	const T2& GetDrugi(int indeks) const { return *_drugi[indeks]; }
	T2& GetDrugi(int indeks) { return *_drugi[indeks]; }
	T1& operator[](int indeks) { return *_prvi[indeks]; }

	friend ostream& operator<<(ostream& COUT, const KolekcijaParova& obj) {
		for (int i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetPrvi(i) << " " << obj.GetDrugi(i) << "\n";
		return COUT;
	}

	void Dodaj(const T1& el1, const T2& el2) {
		if (GetTrenutno() == max) {
			return;
		}
		_prvi[GetTrenutno()] = new T1{ el1 };
		_drugi[GetTrenutno()] = new T2{ el2 };
		_trenutno++;
	}

	KolekcijaParova& DodajNaPoziciju(int lokacija, const T1& el1, const T2& el2) {
		if (lokacija < 0 || lokacija > GetTrenutno()) {
			return *this;
		}
		if (lokacija == GetTrenutno()) {
			Dodaj(el1, el2);
			return *this;
		}
		for (int i = GetTrenutno(); i > lokacija; i--) {
			_prvi[i] = _prvi[i - 1];
			_drugi[i] = _drugi[i - 1];
		}
		_prvi[lokacija] = new T1{ el1 };
		_drugi[lokacija] = new T2{ el2 };
		_trenutno++;

		return *this;
	}

	void UkloniNa(int lokacija) {
		if (lokacija < 0 || lokacija > GetTrenutno()) {
			return;
		}
		_trenutno--;
		for (int i = lokacija; i < GetTrenutno(); i++) {
			_prvi[i] = _prvi[i + 1];
			_drugi[i] = _drugi[i + 1];
		}
	}

	KolekcijaParova* UkloniRaspon(int start, int brojElemenata) {
		if (start + brojElemenata > GetTrenutno() || start < 0 || start > GetTrenutno()) {
			throw exception("Zahtjevani opseg elemenata za ukloniti nije validan!");
		}
		KolekcijaParova* temp = new KolekcijaParova{};
		while (brojElemenata != 0)
		{
			temp->Dodaj(GetPrvi(start), GetDrugi(start));
			UkloniNa(start);
			brojElemenata--;
		}
		return temp;
	}

private:
	void dealocirajElemente() {
		for (int i = 0; i < _trenutno; i++) {
			delete _prvi[i]; _prvi[i] = nullptr;
			delete _drugi[i]; _drugi[i] = nullptr;
		}
	}
};
class DatumVrijeme {
	int* _godina, * _mjesec, * _dan, * _sati, * _minute, * _sekunde;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int
		sati = 0, int minute = 0, int sekunde = 0) {
		_godina = new int(godina);
		_mjesec = new int(mjesec);
		_dan = new int(dan);
		_sati = new int(sati);
		_minute = new int(minute);
		_sekunde = new int(sekunde);
	}
	DatumVrijeme(const DatumVrijeme& obj)
	{
		_godina = new int{ obj.getGodina() };
		_mjesec = new int{ obj.getMjesec() };
		_dan = new int{ obj.getDan() };
		_sati = new int{ obj.getSati() };
		_minute = new int{ obj.getMinute() };
		_sekunde = new int{ obj.getSekunde() };
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if (this == &obj) {
			return *this;
		}
		*_godina = obj.getGodina();
		*_mjesec = obj.getMjesec();
		*_dan = obj.getDan();
		*_sati = obj.getSati();
		*_minute = obj.getMinute();
		*_sekunde = obj.getSekunde();
		return *this;
	}
	~DatumVrijeme() {
		delete _godina; delete _mjesec; delete _dan;
		delete _sati; delete _minute; delete _sekunde;
	}

	int getGodina() const { return *_godina; }
	int getMjesec() const { return *_mjesec; }
	int getDan() const { return *_dan; }
	int getSati() const { return *_sati; }
	int getMinute() const { return *_minute; }
	int getSekunde() const { return *_sekunde; }

	friend ostream& operator<<(ostream& COUT, const DatumVrijeme& obj) {
		COUT << obj.getDan() << "." << obj.getMjesec() << "." << obj.getGodina() << " " << obj.getSati() << ":" << obj.getMinute() << ":" << obj.getSekunde();
		return COUT;
	}

	bool operator==(const DatumVrijeme& obj) const {
		return getGodina() == obj.getGodina() && getMjesec() == obj.getMjesec() && getDan() == obj.getDan() && getSati() == obj.getSati() && getMinute() == obj.getMinute() && getSekunde() == obj.getSekunde();
	}
};
class Proizvod {
	char* _naziv;
	Kategorija _kategorija;
	int _cijena;
public:
	Proizvod(const char* naziv = "", Kategorija kategorija = ELEKTRONIKA, int cijena = 0) : _kategorija(kategorija), _cijena(cijena)
	{
		_naziv = AlocirajTekst(naziv);
	}
	Proizvod(const Proizvod& obj)
	{
		_naziv = AlocirajTekst(obj.GetNaziv());
		_kategorija = obj.GetKategorija();
		_cijena = obj.GetCijena();
	}
	Proizvod& operator=(const Proizvod& obj) {
		if (this == &obj) {
			return *this;
		}
		_naziv = AlocirajTekst(obj.GetNaziv());
		_kategorija = obj.GetKategorija();
		_cijena = obj.GetCijena();
		return *this;
	}
	~Proizvod() {
		delete[] _naziv;
	}

	const char* GetNaziv() const { return _naziv; }
	Kategorija GetKategorija() { return _kategorija; }
	const Kategorija GetKategorija() const { return _kategorija; }
	int GetCijena() const { return _cijena; }
	int GetCijena() { return _cijena; }

	friend ostream& operator<<(ostream& COUT, const Proizvod& p) {
		COUT << p._naziv << " " << KategorijaNazivi[(int)p._kategorija] << " " << p._cijena;
		return COUT;
	}

	bool operator==(const Proizvod& obj) const {
		return GetKategorija() == obj.GetKategorija() && string(GetNaziv()) == obj.GetNaziv() && GetCijena() == obj.GetCijena();
	}
};
class Transakcija {
protected:
	DatumVrijeme _vrijemeRealizacije;
	int _iznos;
public:
	Transakcija(DatumVrijeme vrijemeRealizacije, int iznos = 0) : _vrijemeRealizacije(vrijemeRealizacije), _iznos(iznos)
	{
	}
	Transakcija(const Transakcija& obj)
	{
		_vrijemeRealizacije = obj.GetVrijemeRealizacije();
		_iznos = obj.GetIznos();
	}
	Transakcija& operator=(const Transakcija& obj) {
		if (this == &obj) {
			return *this;
		}
		_vrijemeRealizacije = obj.GetVrijemeRealizacije();
		_iznos = obj.GetIznos();

		return *this;
	}
	virtual ~Transakcija()
	{
	}

	virtual string Info() const = 0;
	virtual Transakcija* Clone() const = 0;

	const DatumVrijeme& GetVrijemeRealizacije() const { return _vrijemeRealizacije; }
	DatumVrijeme& GetVrijemeRealizacije() { return _vrijemeRealizacije; }
	const int GetIznos() const { return _iznos; }
	int& GetIznos() { return _iznos; } //treba & 

	friend ostream& operator<<(ostream& COUT, const Transakcija& obj) {
		COUT << obj.GetVrijemeRealizacije() << " " << obj.GetIznos();
	}
};
class Kupovina : public Transakcija {
	vector<Proizvod> _kupljeniProizvodi;
public:
	Kupovina(DatumVrijeme vrijemeRealizacije) : Transakcija(vrijemeRealizacije, 0)
	{
	}
	Kupovina(const Kupovina& obj) : Transakcija(obj)
	{
		_kupljeniProizvodi = obj.GetProizvodi();
	}
	Kupovina& operator=(const Kupovina& obj) {
		if (this == &obj) {
			return *this;
		}
		_kupljeniProizvodi = obj.GetProizvodi();

		return *this;
	}
	~Kupovina() {

	}

	const vector<Proizvod>& GetProizvodi() const { return _kupljeniProizvodi; }
	vector<Proizvod>& GetProizvodi() { return _kupljeniProizvodi; }

	//05.10.2025 09:30:00 KUPLJENO 1 PROIZVODA U UKUPNOM IZNOSU OD 1500KM
	string Info() const {
		ostringstream forrmatedInfo{};
		forrmatedInfo << setw(2) << setfill('0') << GetVrijemeRealizacije().getDan() << "."
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getMjesec() << "."
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getGodina() << " "
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getSati() << ":"
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getMinute() << ":"
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getSekunde()
			<< " KUPLJENO " << GetProizvodi().size() << " PROIZVODA U IZNOSU OD " << GetIznos() << "KM";
		return forrmatedInfo.str();
	}

	Transakcija* Clone() const {
		return new Kupovina(*this);
	}

	void DodajProizvod(const Proizvod& proizvodZaDodati) {
		_kupljeniProizvodi.push_back(proizvodZaDodati);
		GetIznos() += proizvodZaDodati.GetCijena();
	}

	bool daLiJeProizvodVecKupljen(const Proizvod& proizvodZaProvjeru) const {
		for (auto& i : GetProizvodi()) {
			if (i == proizvodZaProvjeru) {
				return true;
			}
		}
		return false;
	}
};
class Povrat : public Transakcija {
	vector<Proizvod> _vraceniProizvodi;
public:
	Povrat(DatumVrijeme vrijemeRealizacije) : Transakcija(vrijemeRealizacije, 0)
	{
	}
	Povrat(const Povrat& obj) : Transakcija(obj)
	{
		_vraceniProizvodi = obj.GetProizvodi();
	}
	Povrat& operator= (const Povrat& obj) {
		if (this == &obj) {
			return *this;
		}

		_vraceniProizvodi = obj.GetProizvodi();

		return *this;
	}
	~Povrat() {

	}

	const vector<Proizvod>& GetProizvodi() const { return _vraceniProizvodi; }
	vector<Proizvod>& GetProizvodi() { return _vraceniProizvodi; }

	string Info() const {
		ostringstream forrmatedInfo{};
		forrmatedInfo << setw(2) << setfill('0') << GetVrijemeRealizacije().getDan() << "."
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getMjesec() << "."
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getGodina() << " "
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getSati() << ":"
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getMinute() << ":"
			<< setw(2) << setfill('0') << GetVrijemeRealizacije().getSekunde()
			<< " VRACENO " << GetProizvodi().size() << " PROIZVODA U IZNOSU OD " << GetIznos() << "KM";
		return forrmatedInfo.str();
	}

	Transakcija* Clone() const {
		return new Povrat(*this);
	}

	void DodajProizvod(const Proizvod& proizvodZaDodati) {
		_vraceniProizvodi.push_back(proizvodZaDodati);
		GetIznos() += proizvodZaDodati.GetCijena();
	}
};
class Kupac {
	static int _id;
	char* _sifra;
	char* _imePrezime;
	vector<Transakcija*> _transakcije;
public:
	Kupac(const char* imePrezime) {
		_imePrezime = AlocirajTekst(imePrezime);
		_sifra = AlocirajTekst(GenerisiSifru(imePrezime, _id).c_str());
		_id++;
	}
	Kupac(const Kupac& obj)
	{
		_imePrezime = AlocirajTekst(obj.GetImePrezime());
		_sifra = AlocirajTekst(obj.GetSifra());
		alocirajDeepCopyTransakcije(obj);
	}
	Kupac& operator=(const Kupac& obj) {
		if (this == &obj) {
			return *this;
		}
		delete[] _sifra;
		delete[] _imePrezime;
		dealocirajTransakcije();

		_imePrezime = AlocirajTekst(obj.GetImePrezime());
		_sifra = AlocirajTekst(obj.GetSifra());
		alocirajDeepCopyTransakcije(obj);

		return *this;
	}
	~Kupac() {
		delete[] _sifra;
		delete[] _imePrezime;
		dealocirajTransakcije();
	}
	const char* GetSifra() const { return _sifra; }
	const char* GetImePrezime() const { return _imePrezime; }
	vector<Transakcija*>& GetTransakcije() { return _transakcije; }
	const vector<Transakcija*>& GetTransakcije() const { return _transakcije; }

	friend ostream& operator<<(ostream& COUT, const Kupac& kupac) {
		COUT << crt << kupac._imePrezime << " [" << kupac._sifra << "]\n";
		for (int i = 0; i < kupac._transakcije.size(); i++)
			COUT << " - " << kupac._transakcije[i]->Info() << "\n";
		COUT << crt;
		return COUT;
	}
	// DodajTransakciju - oneomguciti dupliranje transakcija sa istim vremenom, kod kupovine onemoguciti
	// dupliranje proizvoda, a povrat omoguciti samo ako je proizvod kupljen.U zavisnosti od rezultata izvrsenja
	// metoda vraca true ili false
	bool DodajTransakciju(Transakcija& transakcijaZaDodati) {

		//Oneomguciti dupliranje transakcija sa istim vremenom:
		for (const auto* t : _transakcije) {
			if (t->GetVrijemeRealizacije() == transakcijaZaDodati.GetVrijemeRealizacije()) {
				return false;
			}
		}

		//Kod kupovine onemoguciti dupliranje proizvoda: 
		if (Kupovina* novaKupovina = dynamic_cast<Kupovina*>(&transakcijaZaDodati)) {
			for (const auto& i : novaKupovina->GetProizvodi()) {
				for (const auto* t : _transakcije) {
					if (const Kupovina* staraKupovina = dynamic_cast<const Kupovina*>(t)) {
						if (staraKupovina->daLiJeProizvodVecKupljen(i) == true) {
							return false;
						}
					}
				}
			}
			_transakcije.push_back(new Kupovina(*novaKupovina));
			return true;
		}

		//Povrat omoguciti samo ako je proizvod kupljen:
		if (Povrat* povrat = dynamic_cast<Povrat*>(&transakcijaZaDodati)) {
			for (auto& i : povrat->GetProizvodi()) {
				bool kupljen = false;
				for (auto* t : _transakcije) {
					if (Kupovina* kupovina = dynamic_cast<Kupovina*>(t)) {
						if (kupovina->daLiJeProizvodVecKupljen(i) == true) {
							kupljen = true;
							break;
						}
					}
				}
				if (kupljen == false) {
					return false;
				}
			}
			_transakcije.push_back(new Povrat(*povrat));
			return true;
		}

		return false;
	}

	bool operator==(const Kupac& obj) const {
		return string(GetImePrezime()) == obj.GetImePrezime() && string(GetSifra()) == obj.GetSifra();
	}

private:
	void dealocirajTransakcije() {
		for (auto* transakcija : _transakcije) delete transakcija;
		_transakcije.clear();
	}

	void alocirajDeepCopyTransakcije(const Kupac& obj) {
		for (auto* i : obj.GetTransakcije()) {
			_transakcije.push_back(i->Clone());
		}
	}
};
int Kupac::_id = 1;
class Prodavnica {
	char* _naziv;
	vector<Kupac> _kupci;
public:
	Prodavnica(const char* naziv) {
		_naziv = AlocirajTekst(naziv);
	}
	Prodavnica(const Prodavnica& obj)
	{
		_naziv = AlocirajTekst(obj.GetNaziv());
		_kupci = obj.GetKupci();
	}
	Prodavnica& operator=(const Prodavnica& obj) {
		if (this == &obj) {
			return *this;
		}
		delete[] _naziv;
		_naziv = AlocirajTekst(obj.GetNaziv());
		_kupci = obj.GetKupci();

		return *this;
	}
	~Prodavnica() {
		delete[] _naziv;
	}
	const char* GetNaziv() const { return _naziv; }
	vector<Kupac>& GetKupci() { return _kupci; }
	const vector<Kupac>& GetKupci() const { return _kupci; }

	friend ostream& operator<<(ostream& COUT, const Prodavnica& obj) {
		COUT << "Naziv prodavnice: " << obj.GetNaziv() << endl;
		COUT << "Kupci: " << endl;
		for (auto& i : obj.GetKupci()) {
			COUT << i << endl;
		}
		return COUT;
	}

	bool daLiJeKupacVecDodan(const Kupac& kupacZaDodati) {
		for (const auto& i : GetKupci()) {
			if (i == kupacZaDodati) {
				return true;
			}
		}
		return false;
	}

	void DodajKupca(const Kupac& kupacZaDodati) {
		if (daLiJeKupacVecDodan(kupacZaDodati) == true) {
			throw exception("Kupac je vec dodan!");
		}
		_kupci.push_back(kupacZaDodati);
	}

	bool RegistrujTransakcijuKupcu(const char* sifra, Kupovina& kupovina) {
		for (auto& kupac : GetKupci()) {
			if (kupac.GetSifra() == string(sifra) == true) {
				if (kupac.DodajTransakciju(kupovina) == true) {
					return true;
				}
			}
		}
		return false;
	}

	KolekcijaParova<Kupac, int, 50> PotrosnjaPoKategoriji(const Kategorija& kategorija) {

		KolekcijaParova<Kupac, int, 50> temp{};

		for (auto& kupac : GetKupci()) {

			int suma = 0;

			for (auto t : kupac.GetTransakcije()) {
				//Za kupovine: 
				if (Kupovina* kupovina = dynamic_cast<Kupovina*>(t)) {
					for (auto& i : kupovina->GetProizvodi()) {
						if (i.GetKategorija() == kategorija) {
							suma += i.GetCijena();
						}
					}
				}
				//Za povrat: 
				if (Povrat* povrat = dynamic_cast<Povrat*>(t)) {
					for (auto& i : povrat->GetProizvodi()) {
						if (i.GetKategorija() == kategorija) {
							suma -= i.GetCijena();
						}
					}
				}
			}
			//Ako ima rezultata, spasi ih u kolekciju: 
			if (suma > 0) {
				temp.Dodaj(kupac, suma);
			}
		}
		return temp;
	}
};

bool UcitajPodatke(const string& putanja, vector<Prodavnica>& prodavnice) {

	//1 - Kreiramo objekat tipa IFSTREAM za kreiranje fajla u kojeg ce se ucitati podaci i proslijedimo putanju iz parametra: 
	ifstream fajl{ putanja };

	//2 - Ako fajl nije uopce otvoren, ne mozemo ni ucitavati podatke: 
	if (!fajl.is_open()) {
		return false;
	}

	//3 - Kreiramo objetke string koji ce u sebi cuvati naziv kupca i prodavnice: 
	string nazivKupca;
	string nazivProdavnice;

	while (getline(fajl, nazivKupca, '|') && getline(fajl, nazivProdavnice)) {
		Prodavnica* trenutnaProdavnica = nullptr;
		for (auto& i : prodavnice) {
			if (i.GetNaziv() == nazivProdavnice) {
				trenutnaProdavnica = &i;
				break;
			}
		}
		if (trenutnaProdavnica == nullptr) {
			prodavnice.push_back(Prodavnica(nazivProdavnice.c_str()));
			trenutnaProdavnica = &prodavnice.back();
		}

		bool kupacPostoji = false;
		for (auto& i : trenutnaProdavnica->GetKupci()) {
			if (i.GetImePrezime() == nazivKupca) {
				kupacPostoji = true;
				break;
			}
		}
		if (kupacPostoji == false) {
			trenutnaProdavnica->DodajKupca(Kupac(nazivKupca.c_str()));
		}
	}
	return true;
}

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite razliku izmedju virtualnih i cistih virtualnih metoda, te korelaciju virtualnih metoda sa polimorfizmom (navesti kratki primjer) ? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasniti razliku izmedju konstruktora kopije i move konstruktora, razlike u implementaciji, te navesti primjere implicitnog i eksplicitnog poziva ? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
int main() {

	cout << PORUKA_TELEFON; cin.get(); system("cls");
	cout << PORUKA_ISPIT; cin.get(); system("cls");
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

	//funkcija za generisanje sifre kupca na osnovu imena i prezimena i rednog broja.
	//sifra je u formatu INICIJALI:TRENUTNA_GODINA-ID_KUPCA, npr. AB:2025 - 003.
	//koristiti trenutnu godinu, dobijenu iz sistema na kome se program izvrsava
	//funkciju koristiti prilikom kreiranja objekta klase Kupac za inicijalizaciju atributa _sifra
	cout << GenerisiSifru("Amina Buric", 3) << endl; // AB:2025-003
	cout << GenerisiSifru("Amar Macic", 15) << endl; // AM:2025-015
	cout << GenerisiSifru("Maid Ramic", 156) << endl << endl; // MR:2025-156

	//za validaciju sifre koristiti funkciju ValidirajSifru koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajSifru("AB:2025-003"))
		cout << "SIFRA VALIDNA\n";
	if (!ValidirajSifru("Ab:2025-003") && !ValidirajSifru("AB2025/003") && !ValidirajSifru("AB-003:2025"))
		cout << "SIFRA NIJE VALIDNA\n";
	cout << endl;

	KolekcijaParova<int, string, 20> listaProizvoda;
	for (int i = 0; i < 10; i++)
		listaProizvoda.Dodaj(i, "Proizvod_" + to_string(i));
	cout << listaProizvoda << crt;

	//DodajNaPoziciju - dodaje par (99, Proizdovi_99) na lokaciju 1 tj.lokaciju definisanu vrijednoscu prvog parametra,
	// a vraca novo stanje kolekcije tj. kolekciju zajedno sa novododatim elementom
	KolekcijaParova<int, string, 20> prosirenaLista =
		listaProizvoda.DodajNaPoziciju(1, 99, "Proizvod_99");
	cout << prosirenaLista << crt;

	// UkloniRaspon - od lokacije definisane prvim parametrom uklanja broj elemenata definisanih drugi parametrom
	// (pocevsi od lokacije 2 ukloni 3 elementa), a vraca pokazivac na kolekciju parova s uklonjenim elementima
	KolekcijaParova<int, string, 20>* uklonjeniProizvodi =
		prosirenaLista.UkloniRaspon(2, 3);
	cout << "Uklonjeni:\n" << *uklonjeniProizvodi << crt;
	/*
	Uklonjeni:
	1 Proizvod_1
	2 Proizvod_2
	3 Proizvod_3
	*/
	cout << "Preostali:\n" << prosirenaLista << crt;
	/*
	Preostali:
	0 Proizvod_0
	99 Proizvod_99
	4 Proizvod_4
	5 Proizvod_5
	6 Proizvod_6
	7 Proizvod_7
	8 Proizvod_8
	9 Proizvod_9
	*/
	*uklonjeniProizvodi = prosirenaLista;
	cout << "Proizvodi:\n" << *uklonjeniProizvodi << crt;
	try
	{
		//baciti izuzetak u slucaju nepostojeceg opsega
		listaProizvoda.UkloniRaspon(3, 10); // izuzetak - neispravan opseg
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}

	DatumVrijeme vrijeme1(5, 10, 2025, 9, 30, 0), vrijeme2(5, 10,
		2025, 10, 15, 0), vrijeme3(5, 10, 2025, 12, 36, 0);

	Proizvod telefon("Telefon FITPhone", ELEKTRONIKA, 1500),
		knjiga("Napredno C++ programiranje", KNJIGE, 55),
		slusalice("Slusalice FSX", ELEKTRONIKA, 129), laptop("Laptop FITLx", ELEKTRONIKA, 1499);

	Kupovina kupovina1(vrijeme1), kupovinaDuplikatVremena(vrijeme1),
		kupovina2(vrijeme2), kupovinaSlusalice(vrijeme2),
		kupovinaDuplikatProizvoda(vrijeme3);

	//dodaje proizvod u listu kupljenih proizvoda i azurira iznos kupovine
	kupovina1.DodajProizvod(telefon);
	kupovina2.DodajProizvod(knjiga);

	//format povratne vrijednosti info metode
	cout << kupovina1.Info() << endl; //05.10.2025 09:30:00 KUPLJENO 1 PROIZVODA U UKUPNOM IZNOSU OD 1500KM

	Kupac amina("Amina Buric"), goran("Goran Skondric"), berun("Berun Agic");

	// DodajTransakciju - oneomguciti dupliranje transakcija sa istim vremenom, kod kupovine onemoguciti
	// dupliranje proizvoda, a povrat omoguciti samo ako je proizvod kupljen.U zavisnosti od rezultata izvrsenja
	// metoda vraca true ili false

	amina.DodajTransakciju(kupovina1);
	amina.DodajTransakciju(kupovina2);
	kupovinaDuplikatProizvoda.DodajProizvod(knjiga);
	//amina je u kupovina2 vec kupila knjigu, duplikat proizvoda, onemoguciti dodavanje
	if (!amina.DodajTransakciju(kupovinaDuplikatProizvoda))
		cout << "Duplikat proizvoda\n";
	kupovinaDuplikatVremena.DodajProizvod(laptop);
	//amina je u kupovina1 vec imala transakciju u vrijeme1, duplikat vremena, onemoguciti dodavanje
	if (!amina.DodajTransakciju(kupovinaDuplikatVremena))
		cout << "Duplikat vremena\n";

	Povrat povratKnjige(vrijeme2);
	povratKnjige.DodajProizvod(knjiga);

	//format povratne vrijednosti Info metode
	cout << povratKnjige.Info() << endl; // 05.10.2025 10:15:00 VRACENO 1 PROIZVODA U UKUPNOM IZNOSU OD 55KM

	//povrat dozvoljen samo ako je proizvod ranije kupljen
	if (amina.DodajTransakciju(povratKnjige))
		cout << "Povrat uspjesno izvrsen\n";

	Prodavnica tehnika("Tehnika"), knjizara("Knjizara");
	tehnika.DodajKupca(amina);
	tehnika.DodajKupca(goran);
	knjizara.DodajKupca(berun);
	try {
		tehnika.DodajKupca(amina); // amina je vec dodata kao kupac
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}

	kupovinaSlusalice.DodajProizvod(slusalice);

	//registraciju transakcije, pored direktnog nacina - preko kupca,
	//je moguce realizovati i u okviru odredjene prodavnice koja ce pronaci kupca
	//po sifri i dodati mu transakciju proslijedjenu kao parametar.u zavisnosti od rezultata
	//izvrsenja metoda vraca true ili false (i dalje vaze pravila vezana za dodavanje transakcije)
	if (!tehnika.RegistrujTransakcijuKupcu(amina.GetSifra(), kupovinaSlusalice))
		cout << "Transakcija registrovana\n";

	vector<Prodavnica> prodavnice;
	prodavnice.push_back(tehnika);
	prodavnice.push_back(knjizara);

	/*
	Funkcija UcitajPodatke ima zadatak ucitati podatke o prodavnicama
   i njihovim kupcima iz fajla cije ime se proslijedjuje kao parametar
	(fajl mozete pronaci zajedno sa ispitnim zadatkom). Svaka linija u
   fajlu treba biti u formatu "ime i prezime kupca|naziv prodavnice".
   Funkcija za
	svaki red u fajlu:
	- unutar vector-a, po nazivu, pronadje ranije dodatu ili
   kreira novu prodavnicu,
	- kreira novog kupca ukoliko vec nije registrovan u naznacenoj
   prodavnici,
	- dodaje kupca u naznacenu prodavnicu (onemoguciti
   dupliciranje kupaca u istoj prodavnici).
	Na kraju, sve prodavnice sa svojim kupcima se trebaju nalaziti u
   proslijedjenom vektoru prodavnice.
	Funkcija vraca true ako je ucitavanje podataka bilo uspjesno (u
   vector ucitan najmanje jedan podatak
	o prodavnici ili kupcu), a false ako se desilo nesto neocekivano
   ili niti jedan podatak nije ucitan.
	Primjer sadrzaja fajla:
	Emina Junuz|Tehnika";
	Jasmin Azemovic|Tehnika";
	Zanin Vejzovic|Knjizara";
	*/

	string nazivFajla = "podaci.txt";
	if (UcitajPodatke(nazivFajla, prodavnice)) cout << "Ucitavanje uspjesno" << crt;

	for (auto& prodavnica : prodavnice)
		cout << prodavnica.GetNaziv() << " sa " << prodavnica.GetKupci().size() << " kupaca" << crt;

	//vraca listu svih kupaca iz prodavnice koji su imali najmanje jednu transakciju u proslijedjenoj kategoriji,
	//te koliko su ukupno potrosili na proizvode iz te kategorije (ukupna potrosnja za kategoriju se
	// izracunava: kupovina - povrat)
	KolekcijaParova<Kupac, int, 50> potrosnja = tehnika.PotrosnjaPoKategoriji(ELEKTRONIKA);
	for (int i = 0; i < potrosnja.GetTrenutno(); i++)
		cout << potrosnja.GetPrvi(i).GetImePrezime() << " [" << potrosnja.GetPrvi(i).GetSifra() << "] " << " potrosio/la " << potrosnja.GetDrugi(i) << " KM na proizvode iz kategorije ELEKTRONIKA" << crt;

	cin.get();
	return 0;
}