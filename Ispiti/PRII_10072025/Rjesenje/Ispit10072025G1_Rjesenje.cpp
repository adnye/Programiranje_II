#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <string>
#include <regex>
#include <exception>
#include <fstream>
using namespace std;
const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA MODIFIKACIJU."
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAINU ZADATKA TREBAJU POSTOJATI. UKOLIKO NISTE ZADOVOLJNI IMPLEMENTACIJOM "
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZE BITI PRAZNA), "
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJU TJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 I RJESENJE TESTIRAJTE U OBAMODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJEŠENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
enum Specializacija {
	KARDIOLOGIJA, ORTOPEDIJA, DERMATOLOGIJA, PEDIJATRIJA, OPSTA_MEDICINA
};
const char* SpecializacijaNazivi[] = {
"KARDIOLOGIJA", "ORTOPEDIJA", "DERMATOLOGIJA", "PEDIJATRIJA", "OPSTA MEDICINA"
};
ostream& operator<<(ostream& COUT, const Specializacija& specijalizacija) {
	switch (specijalizacija)
	{
	case KARDIOLOGIJA:
		COUT << "KARDIOLOGIJA";
		break;
	case ORTOPEDIJA:
		COUT << "ORTOPEDIJA";
		break;
	case DERMATOLOGIJA:
		COUT << "DERMATOLOGIJA";
		break;
	case PEDIJATRIJA:
		COUT << "PEDIJATRIJA";
		break;
	case OPSTA_MEDICINA:
		COUT << "OPSTA MEDICINA";
		break;
	default:
		COUT << "Specijalizacija nije pronadjena.";
		break;
	}
	return COUT;
}
const char* crt = "\n-------------------------------------------\n";
char* AlocirajNiz(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}
int getYearBySystem() { //#include <ctime>
	time_t trenutnoVrijeme = time(nullptr);
	tm lokalnoVrijeme{};
	localtime_s(&lokalnoVrijeme, &trenutnoVrijeme);
	return lokalnoVrijeme.tm_year + 1900;
}
int getLastTwoDigitsOfCurrentYear() {
	int year = getYearBySystem();
	return year % 100;
}
char* GenerisiSifru(const char* imePrezime, int broj) { //#include <string>
	int trenutnaGodina = getLastTwoDigitsOfCurrentYear();
	string godinaStr = to_string(trenutnaGodina);
	string imePrezimeStr = imePrezime;
	string BrojStr = to_string(broj);
	string Sifra{};
	size_t pozicijaPrezimena = imePrezimeStr.find(' ') + 1;
	Sifra += godinaStr;
	Sifra += '-';
	Sifra += toupper(imePrezime[0]);
	Sifra += toupper(imePrezime[pozicijaPrezimena]);
	Sifra += '-';
	if (broj < 10) {
		Sifra += "00";
	}
	else if (broj < 100) {
		Sifra += '0';
	}
	Sifra += BrojStr;
	return AlocirajNiz(Sifra.c_str());
}
bool ValidirajSifru(string sifra) { //#include <regex>
	return regex_match(sifra, regex("25[-]?[\\s]?[A-Z]{2}[-]?[\\s]?[\\d]{3}"));
}
template<class T1, class T2, int max>
class KolekcijaG1 {
	T1* _elementi1[max]{};
	T2* _elementi2[max]{};
	int _trenutno;
public:
	KolekcijaG1()
	{
		_trenutno = 0;
	}
	KolekcijaG1(const KolekcijaG1& obj)
	{
		_trenutno = obj.getTrenutno();
		for (int i = 0; i < getTrenutno(); i++) {
			_elementi1[i] = new T1(obj.getElement1(i));
			_elementi2[i] = new T2(obj.getElement2(i));
		}
	}
	KolekcijaG1& operator=(const KolekcijaG1& obj) {
		if (this == &obj) {
			return *this;
		}
		dealocirajElemente();
		_trenutno = obj.getTrenutno();
		for (int i = 0; i < getTrenutno(); i++) {
			_elementi1[i] = new T1(obj.getElement1(i));
			_elementi2[i] = new T2(obj.getElement2(i));
		}
		return *this;
	}
	~KolekcijaG1() {
		dealocirajElemente();
		_trenutno = 0;
	}
	T1& getElement1(int lokacija) { return *_elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return *_elementi2[lokacija]; }
	const T1& getElement1(int lokacija) const { return *_elementi1[lokacija]; }
	const T2& getElement2(int lokacija) const { return *_elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, KolekcijaG1& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
	void AddElement(const T1& el1, const T2& el2) {
		if (getTrenutno() == max) {
			return;
		}
		_elementi1[getTrenutno()] = new T1(el1);
		_elementi2[getTrenutno()] = new T2(el2);
		_trenutno++;
	}
	KolekcijaG1& InsertAt(int lokacija, const T1& el1, const T2& el2) {
		if (lokacija < 0 || lokacija > getTrenutno() || getTrenutno() == max) {
			return *this;
		}
		if (lokacija == getTrenutno()) {
			AddElement(el1, el2);
			return *this;
		}
		for (int i = getTrenutno(); i > lokacija; i--) {
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}
		_elementi1[lokacija] = new T1(el1);
		_elementi2[lokacija] = new T2(el2);
		_trenutno++;
		return *this;
	}
	void RemoveAt(int lokacija) {
		if (lokacija < 0 || lokacija > getTrenutno()) {
			return;
		}
		delete _elementi1[lokacija];
		delete _elementi2[lokacija];
		_trenutno--;
		for (int i = lokacija; i < getTrenutno(); i++) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
	}
	KolekcijaG1* RemoveRange(int start, int brojElemenataZaUkloniti) { //#include <exception >
			if (start + brojElemenataZaUkloniti > getTrenutno()) {
				throw exception("Zahtjevani opseg elemenata za ukloniti nije validan!");
			}
		KolekcijaG1* temp = new KolekcijaG1{};
		while (brojElemenataZaUkloniti != 0) {
			temp->AddElement(getElement1(start), getElement2(start));
			RemoveAt(start);
			brojElemenataZaUkloniti--;
		}
		return temp;
	}
private:
	void dealocirajElemente() {
		for (int i = 0; i < getTrenutno(); i++) {
			delete _elementi1[i];
			_elementi1[i] = nullptr;
			delete _elementi2[i];
			_elementi2[i] = nullptr;
		}
	}
};
class Termin {
	int* _sati; int* _minute; int* _sekunde;
public:
	Termin(int s = 0, int m = 0, int k = 0) {
		_sati = new int(s);
		_minute = new int(m);
		_sekunde = new int(k);
	}
	Termin(const Termin& obj) :
		_sati{ new int{obj.getSati()} },
		_minute{ new int{obj.getMinute()} },
		_sekunde{ new int{obj.getSekunde()} }
	{
	}
	Termin& operator=(const Termin& obj) {
		if (this == &obj) {
			return *this;
		}
		*_sati = obj.getSati();
		*_minute = obj.getMinute();
		*_sekunde = obj.getSekunde();
		return *this;
	}
	~Termin() {
		delete _sati; delete _minute; delete _sekunde;
	}
	int getSati() const { return *_sati; }
	int getMinute() const { return *_minute; }
	int getSekunde() const { return *_sekunde; }
	friend ostream& operator<<(ostream& COUT, const Termin& t) {
		COUT << *t._sati << ":" << *t._minute << ":" << *t._sekunde;
		return COUT;
	}
	bool operator==(const Termin& obj) const {
		return getSati() == obj.getSati() && getMinute() == obj.getMinute() && getSekunde
		() == obj.getSekunde();
	}
	bool operator!=(const Termin& obj) const {
		return !(obj == *this);
	}
};
class Dogadjaj {
protected:
	Termin _termin;
public:
	Dogadjaj(Termin termin) : _termin(termin) {}
	Dogadjaj(const Dogadjaj& obj)
	{
		_termin = obj.getTermin();
	}
	Dogadjaj& operator=(const Dogadjaj& obj) {
		if (this == &obj) {
			return *this;
		}
		_termin = obj.getTermin();
		return *this;
	}
	virtual ~Dogadjaj() {}
	virtual string Info() const = 0;
	virtual Dogadjaj* Clone() const = 0;
	const Termin& getTermin() const { return _termin; }
	Termin& getTermin() { return _termin; }
	friend ostream& operator<<(ostream& COUT, const Dogadjaj& obj) {
		COUT << "Termin dogadjaja: " << obj.getTermin() << endl;
		return COUT;
	}
};
class Predavanje : public Dogadjaj {
	char* _tema;
	Specializacija _specijalizacija;
public:
	Predavanje(Termin termin, const char* tema, const Specializacija specijalizacija)
		: Dogadjaj(termin),
		_tema{ AlocirajNiz(tema) }
	{
		_specijalizacija = specijalizacija;
	}
	Predavanje(const Predavanje& obj) : Dogadjaj(obj),
		_tema{ AlocirajNiz(obj.GetTema()) }
	{
		_specijalizacija = obj.GetSpecijalizacija();
	}
	Predavanje& operator=(const Predavanje& obj) {
		if (this == &obj) {
			return *this;
		}
		delete[] _tema;
		Dogadjaj::operator=(obj);
		_tema = AlocirajNiz(obj.GetTema());
		_specijalizacija = obj.GetSpecijalizacija();
		return *this;
	}
	~Predavanje() {
		delete[] _tema;
	}
	const char* GetTema() const { return _tema; }
	const Specializacija& GetSpecijalizacija() const { return _specijalizacija; }
	Specializacija& GetSpecijalizacija() { return _specijalizacija; }
	string Info() const { //#include <sstream>
		ostringstream formattedInfo{};
		formattedInfo << GetTema() << ' ' << getTermin() << ' ' << GetSpecijalizacija();
		return formattedInfo.str();
	}
	Dogadjaj* Clone() const override {
		return new Predavanje(*this);
	}
	bool operator==(const Predavanje& obj) const { //Operator== u Termin
		return getTermin() == obj.getTermin() && string(GetTema()) == obj.GetTema() && GetSpecijalizacija() == obj.GetSpecijalizacija();
	}
	bool operator!=(const Predavanje& obj) const {
		return !(obj == *this);
	}
};
class Ucesnik {
	static int _id; //iskoristiti za praćenje rednog broja ucesnika i generisanje jedinstvene sifre
	char* _sifra; //sifra u formatu GG-INBBB, pojasnjena u main funkciji, generisati prilikom kreiranja objekta
	char* _imePrezime;
	vector<Dogadjaj*> _prijavljeni;
public:
	Ucesnik(const char* imePrezime) :
		_imePrezime{ AlocirajNiz(imePrezime) },
		_sifra{ GenerisiSifru(imePrezime, _id++) }
	{
	}
	Ucesnik(const Ucesnik& obj) :
		_imePrezime{ AlocirajNiz(obj.getImePrezime()) },
		_sifra{ AlocirajNiz(obj.getSifra()) }
	{
		deepCopyForPrijavljeni(obj); //Za vector _prijavljeni
	}
	Ucesnik& operator=(const Ucesnik& obj) {
		if (this == &obj) {
			return *this;
		}
		delete[] _imePrezime;
		delete[] _sifra;
		dealocirajDogadjajeUnutarPrijavljeni();
		_imePrezime = AlocirajNiz(obj.getImePrezime());
		_sifra = AlocirajNiz(obj.getSifra());
		deepCopyForPrijavljeni(obj); //Za vector _prijavljeni
		return *this;
	}
	~Ucesnik() {
		delete[] _imePrezime;
		delete[] _sifra;
		dealocirajDogadjajeUnutarPrijavljeni();
	}
	const char* getSifra() const { return _sifra; }
	const char* getImePrezime() const { return _imePrezime; }
	vector<Dogadjaj*>& getDogadjaji() { return _prijavljeni; }
	const vector<Dogadjaj*>& getDogadjaji() const { return _prijavljeni; }
	friend ostream& operator<<(ostream& COUT, const Ucesnik& obj) {
		COUT << "Sifra ucesnika: " << obj.getSifra() << endl;
		COUT << "Ime i prezime ucesnika: " << obj.getImePrezime() << endl;
		COUT << "Termini prijavljenih dogadjaja ucesnika: " << endl;
		for (auto* i : obj.getDogadjaji()) {
			COUT << *i;
		}
		COUT << endl;
		return COUT;
	}
	bool daLiJePredavanjeVecPrijavljeno(const Predavanje& predavanjeZaPrijaviti) const{
		for (const auto* const i : getDogadjaji()) {
		const Predavanje* const predavanje = dynamic_cast<const Predavanje*>(i);
		if (*predavanje == predavanjeZaPrijaviti) { //Operator== u Predavanje
		return true;
		}
		}
		return false;
	}
		bool PrijaviSe(const Predavanje& predavanjeZaPrijaviti) {
		if (daLiJePredavanjeVecPrijavljeno(predavanjeZaPrijaviti) == true) {
			return false;
		}
		_prijavljeni.push_back(predavanjeZaPrijaviti.Clone());
		return true;
	}
	bool operator==(const Ucesnik& obj) const {
		return string(getImePrezime()) == obj.getImePrezime() && string(getSifra()) == obj.getSifra();
	}
	bool operator!=(const Ucesnik& obj) const {
		return !(obj == *this);
	}
	int brojPrijavljenihPredavanja() const {
		return _prijavljeni.size();
	}
private:
	void dealocirajDogadjajeUnutarPrijavljeni() {
		for (auto prijava : _prijavljeni)
			delete prijava;
		_prijavljeni.clear();
	}
	void deepCopyForPrijavljeni(const Ucesnik& obj) {
		for (auto* i : obj.getDogadjaji()) {
			_prijavljeni.push_back(i->Clone());
		}
	}
};
int Ucesnik::_id = 1;
class Tim {
	char* _naziv;
	vector<Ucesnik> _clanovi;
public:
	Tim(const char* naziv) :
		_naziv{ AlocirajNiz(naziv) }
	{
	}
	Tim(const Tim& obj) :
		_naziv{ AlocirajNiz(obj.getNaziv()) }
	{
		_clanovi = obj.getClanovi();
	}
	Tim& operator=(const Tim& obj) {
		if (this == &obj) {
			return *this;
		}
		delete[] _naziv;
		_naziv = AlocirajNiz(obj.getNaziv());
		_clanovi = obj.getClanovi();
		return *this;
	}
	~Tim() {
		delete[] _naziv;
	}
	const char* getNaziv() const { return _naziv; }
	const vector<Ucesnik>& getClanovi() const { return _clanovi; }
	vector<Ucesnik>& getClanovi() { return _clanovi; }
	friend ostream& operator<<(ostream& COUT, const Tim& obj) {
		COUT << "Naziv tima: " << obj.getNaziv() << endl;
		COUT << "Clanovi tima " << "'" << obj.getNaziv() << "': " << endl;
		for (const auto& i : obj.getClanovi()) {
			COUT << i;
		}
		COUT << "~ ~ ~ ~ ~ ~" << endl;
		return COUT;
	}
	bool daLiUcesnikVecPostojiUTimu(const Ucesnik& ucesnikZaDodati) const {
		for (const auto& i : getClanovi()) {
			if (i == ucesnikZaDodati) { //Operator== u Ucesnik
				return true;
			}
		}
		return false;
	}
	void DodajUcesnika(const Ucesnik& ucesnikZaDodati) {
		if (daLiUcesnikVecPostojiUTimu(ucesnikZaDodati) == true) {
			throw exception("Dodavanje ucesnika nije moguce. Ucesnik vec postoji u timu!");
		}
		_clanovi.push_back(ucesnikZaDodati);
	}
	Ucesnik* daLiPostojiUcesnikSaTomSifrom(const string& sifra) {
		for (auto& i : _clanovi) {
			if (i.getSifra() == sifra) {
				return &i;
			}
		}
		return nullptr;
	}
};
/*
Klasa Konferencija omogucava organizaciju i pracenje koji timovi i
ucesnici prisustvuju kojim predavanjima,
ali sama ne sadrzi direktno predavanja, vec ih povezuje preko ucesnika
i timova.
*/
class Konferencija {
	char* _naziv;
	KolekcijaG1<Tim*, Tim*, 20> _timovi;
public:
	Konferencija(const char* naziv) :
		_naziv{ AlocirajNiz(naziv) }
	{
	}
	Konferencija(const Konferencija& obj) :
		_naziv{ AlocirajNiz(obj.getNaziv()) }
	{
		_timovi = obj.getTimoviCopy();
	}
	Konferencija& operator=(const Konferencija& obj) {
		if (this == &obj) {
			return *this;
		}
		delete[] _naziv;
		izbrisiTimoveUnutarKonferencije();
		_naziv = AlocirajNiz(obj.getNaziv());
		_timovi = obj.getTimoviCopy();
		return *this;
	}
	~Konferencija() {
		delete[] _naziv; _naziv = nullptr;
		izbrisiTimoveUnutarKonferencije();
	}
	const char* getNaziv() const { return _naziv; }
	KolekcijaG1<Tim*, Tim*, 20>& getTimovi() { return _timovi; }
	const KolekcijaG1<Tim*, Tim*, 20>& getTimovi() const { return _timovi; }
	KolekcijaG1<Tim*, Tim*, 20> getTimoviCopy() const {
		KolekcijaG1<Tim*, Tim*, 20> temp{};
		for (int i = 0; i < getTimovi().getTrenutno(); i++) {
			temp.AddElement(new Tim{ *getTimovi().getElement1(i) }, new Tim{ *getTimovi().getElement2(i) });
		}
		return temp;
	}
	friend ostream& operator<<(ostream& COUT, const Konferencija& obj) {
		COUT << "Naziv konferencije: " << obj.getNaziv() << endl;
		COUT << "Timovi konferencije " << "'" << obj.getNaziv() << "':" << endl;
		for (int i = 0; i < obj.getTimovi().getTrenutno(); i++) {
			COUT << obj.getTimovi().getElement1(i)->getNaziv() << endl;
			COUT << *obj.getTimovi().getElement1(i) << endl;
			COUT << obj.getTimovi().getElement2(i)->getNaziv() << endl;
			COUT << *obj.getTimovi().getElement2(i) << endl;
		}
		COUT << crt;
		return COUT;
	}
	void DodajTimove(const Tim& tim1, const Tim& tim2) {
		_timovi.AddElement(new Tim{ tim1 }, new Tim{ tim2 });
	}
	Tim* daLiTimPostoji(string imeTima) { //string da se izbjegne strcmp dolje u if iskazu
			for (int i = 0; i < getTimovi().getTrenutno(); i++) {
				if (getTimovi().getElement1(i)->getNaziv() == imeTima) {
					return getTimovi().getElement1(i);
				}
				else if (getTimovi().getElement2(i) -> getNaziv() == imeTima) {
					return getTimovi().getElement2(i);
				}
			}
		return nullptr;
	}
	bool PrijaviDogadjaj(const char* imeTima, const char* sifraUcesnika, const Predavanje& predavanje) {
		//Prvo trazimo tim u kojem ucesnik pripada, i gledamo da li taj tim uopste postoji
			Tim* timUcesnika = daLiTimPostoji(imeTima);
		//Ako taj tim nikako i ne postoji, onda necemo ni prijaviti dogadjaj:
		if (timUcesnika == nullptr) {
			return false;
		}
		//Sada provjeravamo da li postoji ucesnik sa proslijedjenom sifrom
		Ucesnik* ucesnik = timUcesnika -> daLiPostojiUcesnikSaTomSifrom(sifraUcesnika); //U klasi Tim
		//Ako ne postoji taj ucesnik sa proslijedjenom sifrom, ili je on vec prijavljen na proslijedjeno predavanje, necemo prijaviti dogadjaj za njega
			if (ucesnik == nullptr || ucesnik -> daLiJePredavanjeVecPrijavljeno(predavanje)) {
				return false;
			}
		//Ako su sve navedene provjere uredu, onda cemo prijaviti ucesnika sa proslijedjenom sifrom i nazivom tima na proslijedjeno predavanje :
		ucesnik->PrijaviSe(predavanje);
		return true;
	}
	vector<Ucesnik*> operator() (int brojPrijava) {
		vector<Ucesnik*> temp{};
		for (int i = 0; i < getTimovi().getTrenutno(); ++i) {
			Tim* tim1 = getTimovi().getElement1(i);
			Tim* tim2 = getTimovi().getElement2(i);
			// Prolazak kroz clanove prvog tima
			for (Ucesnik& i : tim1->getClanovi()) {
				if (i.brojPrijavljenihPredavanja() >= brojPrijava) { //U klasi Ucesnik
					temp.push_back(&i); //vidjeti napomenu ispod:
				}
			}
			//NAPOMENA:: Da bi se u vector<Ucesnik*> pohranila adresa ucesnika iz postojeceg vectora _clanovi, mora stajati Ucesnik& i : tim1 getClanove()..., jer se tad uzima originalna adresa ucesnika iz vectora _clanovi i upravo se ta push - back - a u temp, ako bi izostavili tu onda bi se pokusavala push backati adresa kopije...
				// Prolazak kroz clanove drugog tima
				for (Ucesnik& i : tim2->getClanovi()) {
					if (i.brojPrijavljenihPredavanja() >= brojPrijava) { //U klasi Ucesnik
						temp.push_back(&i);
					}
				}
		}
		return temp;
	}
private:
	void izbrisiTimoveUnutarKonferencije() {
		for (int i = 0; i < getTimovi().getTrenutno(); i++) {
			delete _timovi.getElement1(i);
			_timovi.getElement1(i) = nullptr;
			delete _timovi.getElement2(i);
			_timovi.getElement2(i) = nullptr;
		}
	}
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//FILEOVI....
Tim* PronadiTimZaNaziv(const string& nazivTima, vector<Tim>& timovi) {
	for (auto& tim : timovi) {
		if (tim.getNaziv() == nazivTima) {
			return &tim;
		}
	}
	timovi.push_back(Tim{ nazivTima.c_str() });
	return &timovi.back();
}
bool DaLiUcesnikPostojiUTimu(const string& imePrezimeUcesnika, const Tim& tim) {
	for (const auto& ucesnik : tim.getClanovi()) {
		if (ucesnik.getImePrezime() == imePrezimeUcesnika) {
			return true;
		}
	}
	return false;
}
bool UcitajUcesnike(const string& pathToFile, vector<Tim>& timovi) { //#include <fstream>
	ifstream file{ pathToFile };
	if (!file.is_open()) {
		return false;
	}
	string line;
	while (std::getline(file, line)) {
		istringstream lineStream{ line };
		string imePrezimeUcesnika;
		string nazivTima;
		getline(lineStream, imePrezimeUcesnika, '|');
		getline(lineStream, nazivTima);
		Tim* timZaPronaci = PronadiTimZaNaziv(nazivTima, timovi);
		if (!DaLiUcesnikPostojiUTimu(imePrezimeUcesnika, *timZaPronaci)) {
			timZaPronaci -> DodajUcesnika(Ucesnik{ imePrezimeUcesnika.c_str() });
		}
	}
	return true;
}
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite razliku između virtualnih i cistih virtualnih metoda, te korelaciju virtualnih metoda sa polimorfizmom(navesti kratki primjer) ? \n";
		return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasniti razliku izmedju konstruktora kopije i move konstruktora, razlike u implementaciji, te navesti primjere implicitnog i eksplicitnog poziva ? \n";
		return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
int main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	/* sifra korisnika treba biti u formatu GG-IN-BBB pri cemu su:
	GG - posljednje dvije cifre trenutne godine (npr.za 2025 -
	> 25), preuzeti vrijednost iz sistema
	IN - inicijali ucesnika, velika slova(prvo slovo imena i prezimena)
	BBB → trocifreni redni broj ucesnika kreiran na osnovu _id-a (npr. 001, 023, 105)
	validnom sifrom treba smatrati i onu koja umjesto znaka crtica
	'-' ima znak razmak npr: 25 DM 003 ili 25 DM-003
	*/
	cout << GenerisiSifru("Denis Music", 3) << endl;//treba vratiti 25-DM-003
	cout << GenerisiSifru("Jasmin Azemovic", 14) << endl;//treba vratiti 25-JA-014
	cout << GenerisiSifru("Goran skondric", 156) << endl;//treba vratiti 25-GS-156
	cout << GenerisiSifru("emina junuz", 798) << endl;//treba vratiti 25-EJ-798
	//Za validaciju sifre koristiti funkciju ValidirajSifru koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.Pored navedenih,
	cout << endl;
	if (ValidirajSifru("25-DM-003"))
		cout << "SIFRA VALIDNA" << endl;
	if (ValidirajSifru("25-JA-014") && ValidirajSifru("25-JA 014"))
		cout << "SIFRA VALIDNA" << endl;
	if (!ValidirajSifru("25-GS-15") || !ValidirajSifru("25-Gs135") || !ValidirajSifru("25-GS-153G"))
		cout << "SIFRA NIJE VALIDNA" << endl;
	cout << crt;
	int kolekcijaTestSize = 9;
	KolekcijaG1<int, string, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, "Vrijednost -> " + to_string(i));
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti drugog i treceg
	 parametra na lokaciju koja je definisana prvim parametrom. Povratna
	 vrijednost metode
	je objekat (pozivaoc metode, u konkretnom slucaju objekat
	 kolekcija1) u okviru koga su, na definisanu lokaciju, dodati
	 proslijedjeni parametri.
	Nakon izvrsenja metode InsertAt, oba objekta, parovi1 i parovi2,
	 bi trebali posjedovati sljedeci sadrzaj:
	0 Vrijednost -> 0
	10 Vrijednost -> 10
	1 Vrijednost -> 1
	2 Vrijednost -> 2
	* ....
	*/
	KolekcijaG1<int, string, 10> kolekcija2 = kolekcija1.InsertAt(1, 10, "Vrijednost-> 10");
		cout << kolekcija2 << crt;
	/*Metoda RemoveRange kao prvi parametar prihvata pocetnu lokaciju
	 a kao drugi parametar broj elemenata koje, od pocetne lokacije uklanja
	 iz kolekcije koja je pozvala
	tu metodu. U slucaju da zahtijevani broj elemenata ne postoji u
	 kolekciji metoda treba baciti izuzetak.
	Na kraju, metoda treba da vrati pokazivac na novi objekat tipa
	 Kolekcija koji sadrzi samo uklonjene elemente*/
	KolekcijaG1<int, string, 10>*kolekcija3 =
		kolekcija1.RemoveRange(1, 3);//uklanja 3 elementa pocevsi od lokacije
	cout << "Uklonjeni:\n" << *kolekcija3;
	cout << "Preostali:\n" << kolekcija1;
	try {
		kolekcija3 -> RemoveRange(2, 3); //pokusavaju se ukloniti nepostojeći elementi
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	delete kolekcija3;
	kolekcija1 = kolekcija2;
	cout << kolekcija1 << crt;
	Termin termin1(19, 02, 30), termin2(10, 30, 40), termin3(14, 15, 20), termin4(16,
		45, 20);
	Predavanje oboljenja_srca(termin1, "Oboljenja srca", KARDIOLOGIJA);
	Predavanje uv_zracenja(termin2, "Uloga UV zracenja u koznim oboljenjima", DERMATOLOGIJA);
	Predavanje anemije(termin3, "Anemije u svakodnevnoj praksi", OPSTA_MEDICINA);
	Ucesnik emina("Emina Junuz"), goran("Goran Skondric"), azra("Azra Maric"), tajib(
		"Tajib Hero");
	//metoda PrijaviSe dodaje prijavu na predavanje ucesniku, ukoliko je prijava uspjesna, vraca true, a usuprotnom false.
		//onemoguciti dupliranje prijava na isto predavanje
	emina.PrijaviSe(oboljenja_srca);
	emina.PrijaviSe(anemije);
	goran.PrijaviSe(oboljenja_srca);
	goran.PrijaviSe(uv_zracenja);
	tajib.PrijaviSe(uv_zracenja);
	//info metoda vraca sve detalje o dogadjaju u string formatu npr.: 19:02 : 30 Oboljenja srca KARDIOLOGIJA
		if (!emina.PrijaviSe(oboljenja_srca)) {
			cout << "Ucesnik " << emina.getImePrezime() << " vec prijavljen na predavanje " << oboljenja_srca.Info() << crt;
		}
	Tim timAlpha("Tim Alpha"), timBeta("Tim Beta");
	//metoda DodajUcesnika treba da doda ucesnika u tim, ukoliko ucesnik vec nije clan tima, u suprotnom treba baciti izuzetak.
		timAlpha.DodajUcesnika(emina); timAlpha.DodajUcesnika(goran);
	timBeta.DodajUcesnika(azra); timBeta.DodajUcesnika(tajib);
	try {
		timAlpha.DodajUcesnika(emina);//emina je vec clanica tima Alpha
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << "\n";
	}
	Konferencija savremena_medicina("Umjetna inteligencija u dijagnostici i lijecenju– novo lice medicine");
		savremena_medicina.DodajTimove(timAlpha, timBeta);
	//ispisuje naziv konferencije, nazive timova i podatke o svim clanovima tima
	cout << savremena_medicina;
	//metoda PrijaviDogadjaj treba omoguciti prijavu dogadjaja / predavanja ucesniku/ clanu proslijedjenog tima.na osnovu poruka
	//koje se ispisuju u nastavku, implementirati metodu PrijaviDogadjaj tako da se prijave vrse samo na osnovu ispravnih podataka.
		if (savremena_medicina.PrijaviDogadjaj(timAlpha.getNaziv(), emina.getSifra(), uv_zracenja))
			cout << "Prijava uspjesna" << crt;
	if (!savremena_medicina.PrijaviDogadjaj("Tim Gamma", emina.getSifra(), anemije))
		cout << "Pokusaj prijave dogadjaja za nepostojeci tim" << crt;
	if (!savremena_medicina.PrijaviDogadjaj(timAlpha.getNaziv(), emina.getSifra(), uv_zracenja))
		cout << "Pokusaj dupliranja prijave predavanja" << crt;
	if (!savremena_medicina.PrijaviDogadjaj(timAlpha.getNaziv(), azra.getSifra(), uv_zracenja))
		cout << "Ucesnik nije clan proslijedjenog tima" << crt;
	if (!savremena_medicina.PrijaviDogadjaj(timAlpha.getNaziv(), "24-GX002", anemije))
		cout << "Prijava sa nepostojecom sifrom nije uspjela." << crt;
	//metoda vraca sve ucesnike koji su se na odredjenoj konferenciji prijavili na minimalno proslijedjeni broj predavanja
		vector<Ucesnik*> vrijedniUcesnici = savremena_medicina(2);
	for (auto ucesnik : vrijedniUcesnici)
		cout << ucesnik->getImePrezime() << "\n";
	/*
	Funkcija UcitajUcesnike ima zadatak ucitati podatke o ucesnicima i
	 njihovim timovima iz fajla cije ime se proslijedjuje kao parametar
	(fajl mozete pronaci zajedno sa ispitnim zadatkom). Svaka linija u
	 fajlu treba biti u formatu "ime i prezime|naziv tima". Funkcija za
	svaki red u fajlu:
	- unutar vector-a, po nazivu, pronadje ranije dodati ili
	 kreira novi tim,
	- kreira novog ucesnika ukoliko vec nije dio tog tima,
	- dodaje ucesnika u odgovarajuci tim (onemoguciti dupliciranje
	 korisnika u istom timu).
	Na kraju, svi timovi sa svojim clanovima se nalaze u
	 proslijedjenom vektoru timovi.
	Funkcija vraca true ako je ucitavanje podataka bilo ouspjesno, a
	 false ako se desilo nesto neocekivano.
	Primjer sadrzaja fajla:
	Goran Skondric|Tim Alpha
	Emina Junuz|Tim Alpha
	Azra Maric|Tim Beta
	Tajib Hero|Tim Beta
	*/
	vector<Tim> timoviIzFajla;
	if (UcitajUcesnike("ucesnici.txt", timoviIzFajla))
		cout << "Ucitavanje podataka USPJESNO.\n";
	else
		cout << "Ucitavanje podataka NEUSPJESNO.\n";
	for (auto& tim : timoviIzFajla)
		cout << tim << crt;
	cin.get();
	return 0;
}