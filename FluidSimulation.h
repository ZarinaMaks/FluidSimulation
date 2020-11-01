class VectorField
{

private: 
	Vector*** vectors;
	int sizeX;
	int sizeY;
	int sizeZ;

public:
	VectorField();
	VectorField(const VectorField& field);
	const Vector& get(const int& i, const int& j, const int& k);
	Vector& get(const int& i, const int& j, const int& k);
	real divergence(const int& i, const int& j, const int& k) const;
	real laplasian(const int& i, const int& j, const int& k) const;
	void clear();
	~VectorField();
	//TODO: add more methods
}

class ScalarField
{
private:
	real*** scalars;
	int sizeX;
	int sizeY;
	int sizeZ;

public:
	ScalarField();
	ScalarField(const ScalarField& field);
	const real& get(const int& i, const int& j, const int& k) const;
	real& get(const int& i, const int& j, const int& k);
	Vector gradient(const int& i, const int& j, const int& k) const;
	void clear();
	~ScalarField();
	//TODO: add more methods
}

VectorField& operator=(const VectorField& field) 
{

}

ScalarField& operator=(const ScalarField& field)
{

}

