#ifndef SICT__Product_H_
#define SICT__Product_H_
#include "Streamable.h"
#include "general.h"

namespace sict {
		class Product : public Streamable {
				char sku_[MAX_SKU_LEN + 1];
				char * name_;
				double price_;
				bool taxed_;
				int quantity_;
				int qtyNeeded_;

				//public member functions and constructors
		public:
				Product();
				Product(const char*, const char*, double x = 0.0, int i = 0, bool = true);

				//copy con
				Product(const Product&);

				//virtual destructor
				virtual ~Product();

				//setters
				void sku(const char*);
				void price(double);
				void name(const char*);
				void taxed(bool);
				void quantity(int);
				void qtyNeeded(int);

				//getters(queries)
				const char* sku() const;
				double price() const;
				const char* name() const;
				bool taxed() const;
				int quantity() const;
				int qtyNeeded() const;
				double cost() const;
				bool isEmpty() const;

				//member operator overloads
				Product& operator=(const Product&);
				bool operator==(const char*);
				int operator+=(int);
				int operator-=(int);

		};
		//Non-Member operator overload
		double operator+=(double&, const Product&);

		//Non - member IO operator overloads:
		std::ostream& operator<<(std::ostream& os, const Product& pr);
		std::istream& operator>>(std::istream& is, Product& pr);
}

#endif