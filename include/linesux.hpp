class LinesDAW;

class LinesUX {
   protected:
	LinesDAW* daw;

   public:
	LinesUX(LinesDAW* daw) { this->daw = daw; };
	virtual ~LinesUX() {};
	virtual int start() = 0;  // :)
	virtual int run() = 0;
	virtual void exit() = 0;
};