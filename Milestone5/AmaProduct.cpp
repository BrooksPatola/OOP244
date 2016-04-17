#include "AmaProduct.h"
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

namespace sict {

		//constructor
		AmaProduct::AmaProduct(char tag) {
				fileTag_ = tag;

		}

		const char* AmaProduct::unit()const {
				return unit_;
		}

		void AmaProduct::unit(const char* value) {
				strncpy(unit_, value, 11);
		}

		std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const {
				file << fileTag_ << "," 
						<< sku() << ',' 
						<< name() << ','
						<< price() << ',' 
						<< taxed() << ',' 
						<< quantity() << ','
						<< unit_  << ','
						<< qtyNeeded();
				if (addNewLine) {
						file << endl;
				} 
				return file;
		}

		std::fstream& AmaProduct::load(std::fstream& file) {
				char s[MAX_SKU_LEN +1];
				char n[20];
				char u[11];
				char t;
				double p;
				int q;
				int qN;

				file.getline(s, MAX_SKU_LEN +1, ',');
				file.getline(n, 20, ',');
				file >> p;
				file.ignore();
				file.get(t);
				file.ignore();
				file >> q;
				file.ignore();
				file.getline(u, 11, ',');
				file >> qN;
				file.ignore();

				sku(s);
				name(n);
				price(p);
				if (t == '1') {
						taxed(true);
				}
				else {
						taxed(false);
				}

				quantity(q);
				unit(u);
				qtyNeeded(qN);

				return file;
		}

		std::ostream& AmaProduct::write(std::ostream& os, bool linear)const {
				if (err_.isClear() == false) {
						return os << err_;
				}

				else {
						if (linear) {
								os  << setfill(' ')<< left << setw(MAX_SKU_LEN) << sku() << '|'
										<< setw(20) << name() << '|' << right
										<< setw(7) << fixed << setprecision(2) << cost() << '|'
										<< setw(4) << quantity() << '|' << left << setw(10)
										<< unit() << '|' << right << setw(4) << qtyNeeded()
										<< '|';

						}
						else {
								os << "Sku: " << sku() << endl
										<< "Name: " << name() << endl
										<< "Price: " << price() << endl;
								if (taxed() == true) {
										os << "Price after tax: " << cost() << endl;
								}
								else {
										os << "Price after tax: N/A" << endl;
								}

								os << "Quantity On Hand: " << quantity() << " " << unit() << endl
										<< "Quantity Needed: " << qtyNeeded();

						}
						return os;
				}
		}
		
		std::istream& AmaProduct::read(std::istream& istr) {
				char s[MAX_SKU_LEN];
				char n[20];
				char u[11];
				char t;
				double p;
				int q;
				int qN;

				err_.clear();

				if (istr.fail() == false) {
						cout << "Sku: ";
						istr.getline(s, MAX_SKU_LEN, '\n');
					
						if (istr.fail() == false) {
								sku(s);
						}

						cout << "Name: ";
						istr.getline(n, 20, '\n');
						if (istr.fail() == false) {
								name(n);
						}

						cout << "Unit: ";
						istr.getline(u, 11, '\n');
						if (istr.fail() == false) {
								unit(u);
						}

						cout << "Taxed? (y/n): ";
						
						istr >> t;
					
						if (t == 'Y' || t == 'y') {
								
								taxed(true);
								istr.clear(); 
								
						}
						else if (t == 'N' || t == 'n') {

								taxed(false);
								istr.clear();
						}
						
						else {
								err_.message("Only (Y)es or (N)o are acceptable");
								istr.setstate(ios::failbit);
						}

						cout << "Price: ";
						if (err_.isClear()) {
								
								istr >> p;
								if (istr.fail()) {
										err_.message("Invalid Price Entry");
								}
								else {
										price(p);
								}
						}
						if (err_.isClear()){
								cout << "Quantity On hand: ";
								istr >> q;
								if (istr.fail()) {
										err_.message("Invalid Quantity Entry");
								}
								else {
										quantity(q);
								}

						}
						if (err_.isClear()) {
								cout << "Quantity Needed: ";
								istr >> qN;
								if (istr.fail()) {
										err_.message("Invalid Quantity Needed Entry");
								}
								else {
										qtyNeeded(qN);
								}
						}

				}
				return istr;

		}

}