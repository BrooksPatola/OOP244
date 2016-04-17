#include <cstring>
#include <iomanip>
#include "AidApp.h"
using namespace std;

namespace sict {

		AidApp::AidApp(const char* filename) {
				strncpy(filename_, filename, 256);

				for (int i = 0; i < MAX_NO_RECS; i++) {
						product_[i] = nullptr;
				}

				noOfProducts_ = 0;
				loadRecs();
		}


		void AidApp::pause()const {

				cout << "Press Enter to continue..." << endl;
				cin.ignore(1000, '\n');
		}

		int AidApp::menu() {
				int x;

				cout << "Disaster Aid Supply Management Program" << endl
						<< "1- List products" << endl
						<< "2- Display product" << endl
						<< "3- Add non-perishable product" << endl
						<< "4- Add perishable product" << endl
						<< "5- Add to quantity of purchased products" << endl
						<< "0- Exit Program" << endl
						<< "> ";
				cin >> x;
				if (cin.fail() || x >= 6) {
						cin.clear();
						cin.ignore();
						x = -1;
				}
				return x;
		}

		void AidApp::loadRecs() {

				int i = 0;
				char p;

				datafile_.open(filename_, ios::in);
				if (datafile_.fail()) {
						datafile_.clear();
						datafile_.close();
						datafile_.open(filename_, ios::out);
						datafile_.close();
				}
				else {
						while (!datafile_.fail()) {
								//product = nullptr;
								if (!product_[i]) {
										delete product_[i];
								}
								datafile_ >> p;
								if (p == 'P') {
										AmaPerishable* perishable = new AmaPerishable;
										product_[i] = perishable;
								}
								else if (p == 'N') {
										AmaProduct* product = new AmaProduct;
										product_[i] = product;
								}
								if (p == 'P' || p == 'N') {

										datafile_.get(p);
										product_[i]->load(datafile_);
										i++;

								}
						}
						noOfProducts_ = i;
				}

				datafile_.close();

		}

		void AidApp::saveRecs() {
				datafile_.open(filename_, ios::out);
				for (int i = 0; i < noOfProducts_; i++) {
						product_[i]->store(datafile_);
				}
				datafile_.close();
		}

		void AidApp::listProducts()const {
				double totalCost = 0;

				cout <<
						"Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl
						<< "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

				for (int i = 0; i < noOfProducts_; i++) {
						totalCost += *product_[i];
						cout << setfill(' ') << right << setw(4) << (i + 1) << " | " << *product_[i] << endl;
						if (i >= 10) {
								pause();
						}
				}

				cout << "---------------------------------------------------------------------------" << endl
						<< "Total cost of support: $" << fixed << setprecision(2) << totalCost << endl;

		}


		int AidApp::SearchProducts(const char* sku)const {
				int match = -1;

				for (int i = 0; i < noOfProducts_; i++) {
						if (*product_[i] == sku) {
								match = i;
						}
						i++;
				}
				return match;
		}


		void AidApp::addQty(const char* sku) {
				int search = SearchProducts(sku);
				int qty = 0;
				int req = 0;



				if (search >= 0) {
						//product_[i] = product_[search];
						product_[search]->write(cout, false);

						cout << "Please enter the number of purchased items: ";
						cin >> qty;
						if (cin.fail()) {
								cout << "Invalid quantity value!" << endl;
						}
						else {
								req = product_[search]->qtyNeeded() - product_[search]->quantity();
								if (qty <= req) {
										// += qty;
										product_[search]->quantity(product_[search]->quantity() + qty);
								}
								else {
										//+= req;
										product_[search]->quantity(product_[search]->qtyNeeded());
										cout << "Too many items; only " << product_[search]->quantity() - product_[search]->qtyNeeded();
										cout << " is needed, please return the extra ";
										cout << search << "items." << endl;
								}
								saveRecs();
								cout << "Updated!" << endl;
						}
				}
				else {
						cout << "Not found!" << endl;
				}
				cin.clear();
				cin.ignore(1000, '\n');
		}



		void AidApp::addProduct(bool isPerishable) {


				if (isPerishable) {
						AmaPerishable* perishable = new AmaPerishable;
						perishable->read(cin);
						if (cin.fail()) {
								cout << *perishable << endl;
						}
						else {
								product_[noOfProducts_] = perishable;
								saveRecs();
								cout << "Product added" << endl;
						}
						delete perishable;
				}
				else {
						AmaProduct* product = new AmaPerishable;
						product->read(cin);
						if (cin.fail()) {
								cout << *product << endl;
						}
						else {
								product_[noOfProducts_] = product;
								saveRecs();
								cout << "Product added" << endl;
						}
						delete product;
				}

				cin.clear();
				fflush(stdin);

		}

		int AidApp::run() {

				int selection;
				int result;
				char sku[MAX_SKU_LEN];


				while ((selection = menu()) != 0) {
						if (selection == 1) {
								listProducts();
								pause();
						}
						else if (selection == 2) {
								cout << "Please enter the SKU:  ";
								cin >> sku[MAX_SKU_LEN];
								result = SearchProducts(sku);
								if (result != -1) {
										addQty(sku);
								}
						}
								if (selection == 3) {

										addProduct(true);
										loadRecs();
									
								}
								else if (selection == 4) {

										addProduct(false);
										loadRecs();
							

								}
								else if (selection == 5) {
										cout << "Please enter the SKU:  ";
										cin >> sku;
										addQty(sku);

								}
								else {
										cout << " === Invalid Selection, try again. === ";
												pause();
										
								}
						
								
						

				}
				cout << "Goodbye!!" << endl;
				return 0;
		}
}
