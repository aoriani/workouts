#include <iostream>
#include <iomanip>
using namespace std;

/**
 ** Implementation of the Builder Patter on C++
 ** following the receipt of Effective Java 2nd
 ** 
 ** My C++ skills are somewhat rusty, specially after C++11/14
 ** I hope I haven't done anything stupid
 **/


class NutritionFacts 
{

	public:
		class Builder;


	private:
		const int calorias;
		const float sodium;
		const float fat;
		const float sugar;

		NutritionFacts(const NutritionFacts::Builder& builder):calorias(builder.calorias), sodium(builder.sodium), fat(builder.fat), sugar(builder.sugar) {} 


	public:
		friend ostream& operator<<(ostream& output, const NutritionFacts& nutritionFacts) 
		{
			output<<"calorias "<<nutritionFacts.calorias<<" sodium "
					<<nutritionFacts.sodium<<" fat " <<nutritionFacts.fat<<" sugar "<<nutritionFacts.sugar<<endl;
			return output;
		}

		class Builder {
			friend class NutritionFacts;
			private:
				int calorias;
				float sodium;
				float fat;
				float sugar;

			public:
				Builder() {	calorias = sodium = fat = sugar = 0;}
				Builder& setCalorias(int cal){ calorias = cal; return *this;}
				Builder& setSodium(float sod){ sodium = sod; return *this;}
				Builder& setSugar(float su){ sugar = su; return *this;}
				Builder& setFat(float fa){ fat = fa; return *this;}

				NutritionFacts build() {
					return NutritionFacts(*this);
				}


		};
};

int main() {

	NutritionFacts::Builder builder;
	NutritionFacts&& facts = builder.setCalorias(2).setFat(0.5f).build();

	cout<<facts;

	return 0;
}

