class THE_BATTLE_OF_MALDON_API Enviroment {
private:
	Enviroment(){

	}

	static Enviroment* enviroment;
public:
	static Enviroment* GetEnviroment(){
		return enviroment;
	}



};