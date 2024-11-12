class LinesDAW;
class RtAudio;

class LinesUX {
   protected:
	LinesDAW* daw;

   public:
	LinesUX() {};
	virtual ~LinesUX() {};
	virtual LinesDAW* createLines(RtAudio* rtAudio) = 0;
	void init(LinesDAW* daw) { this->daw = daw; }
	virtual int start() = 0;
	virtual int run() = 0;
	virtual void exit() = 0;
};