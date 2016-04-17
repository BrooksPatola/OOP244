#include <iostream>
#include <cstring>
#include "Product.h"

namespace sict {

		Product::Product() {
				sku_[0] = '\0';
				name_ = nullptr;
				price_ = 0;
				taxed_ = false; // maybe true
				quantity_ = 0;
				qtyNeeded_ = 0;
		}


		Product::Product(const char* s, const char* n, double x, int i, bool tax) {
				//	Copies the SKU into the corresponding member variable up to MAX_SKU_LEN characters. 
				//still hae to implement  as just does (strcpy(x,y)) right now
				sku(s);
				name(n);
				price(x);
				qtyNeeded(i);
				quantity(0);
				taxed(tax);
		}

		//copy con
		Product::Product(const Product& other) {
				//
				sku(other.sku_);
				name(other.name_);
				price(other.price_);
				taxed(other.taxed_);
				quantity(other.quantity_);
				qtyNeeded(other.qtyNeeded_);


		}

		Product& Product::operator=(const Product& other) {
				//may not need to test this
				if (this != &other) {
						sku(other.sku_);
						name(other.name_);
						price(other.price_);
						taxed(other.taxed_);
						quantity(other.quantity_);
						qtyNeeded(other.qtyNeeded_);
				}
				return *this;

		}

		//setters
		void Product::sku(const char* sku) {
				strncpy(sku_, sku, MAX_SKU_LEN);
		}

		void Product::price(double price) {
				price_ = price;
		}

		void Product::name(const char* name) {
				name_ = new char[strlen(name) + 1];
				strcpy(name_, name);

		}

		void Product::taxed(bool taxed) {
				taxed_ = taxed;
		}

		void Product::quantity(int quantity) {
				quantity_ = quantity;
		}

		void Product::qtyNeeded(int qty) {
				qtyNeeded_ = qty;
		}

		//getters
		const char* Product::sku() const {
				return sku_;
		}

		double Product::price() const {
				return price_;
		}

		const char* Product::name() const {
				return name_;
		}

		bool Product::taxed() const {
				return taxed_;
		}

		int Product::quantity() const {
				return quantity_;
		}

		int Product::qtyNeeded() const {
				return qtyNeeded_;
		}

		double Product::cost() const {
				double cost = price_;
				if (taxed_) {
						cost *= TAX + 1;
				}
				return cost;
		}

		bool Product::isEmpty() const {
				return sku_[0] == '\0';
		}

		bool Product::operator==(const char* sku) {
				return strcmp(sku_, sku) == 0;
		}

		int Product::operator+=(int value) {
				return quantity_ += value;
		}

		int Product::operator-=(int value) {
				return quantity_ -= value;
		}

		double operator+=(double& d, const Product& P) {
				d += P.cost() * P.quantity();
				return d;
		}

		std::ostream& operator<<(std::ostream& os, const Product& pr) {
				return pr.write(os, true);
		}

		std::istream& operator>>(std::istream& is, Product& pr) {
				return pr.read(is);
		}

		Product::~Product() {

				delete[] name_;

		}


}