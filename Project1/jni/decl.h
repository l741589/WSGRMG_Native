#pragma once
/*namespace cocos2d{
    class Director{
    public:
        static Director*getInstance();
        virtual init();
    };
}*/

/** @def CC_FORMAT_PRINTF(formatPos, argPos)
* Only certain compiler support __attribute__((format))
*
* @param formatPos 1-based position of format string argument.
* @param argPos    1-based position of first format-dependent argument.
*/
#if defined(__GNUC__) && (__GNUC__ >= 4)
#define CC_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
#if __has_attribute(format)
#define CC_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#endif // __has_attribute(format)
#else
#define CC_FORMAT_PRINTF(formatPos, argPos)
#endif

#define schedule_selector(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

namespace cocos2d{
    const char* cocos2dVersion();
	/*class Ref {
	public:
		void retain();
		void release();

	};
	typedef void (Ref::*SEL_SCHEDULE)(float);

	class Scheduler {
	public:
		void schedule(SEL_SCHEDULE selector, Ref *target, float interval, bool paused);
		void unschedule(SEL_SCHEDULE selector, Ref *target);
	};

	extern "C" void*_ZN7cocos2d16FileUtilsAndroid12assetmanagerE;
	*/
	class Vec2 {
	public:
		float x;
		float y;
	};
	class Size {
	public:
		float width;
		float height;
	};
	class Node {
	public:
		virtual void addChild(Node * child, int localZOrder);
	};
	class Scene :public Node{
	public:
		static Scene *create();
	};
	class Director {
	public:
		static Director* getInstance();
		void* getTextureCache() const;
		void replaceScene(Scene *scene);
		const Size& getWinSize() const;
	};

	class FileUtils {
	public:
		static FileUtils* getInstance();
		virtual const std::vector<std::string>* getSearchPaths() const;
	};

	class __String {
	public:
		static __String* createWithFormat(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
		const char* getCString() const;
		std::string _string;
	};

	class ZipUtils {
	public:
		static bool isCCZBuffer(const unsigned char *buffer, ssize_t len);
		static bool isGZipBuffer(const unsigned char *buffer, ssize_t len);
	};

	
	class Sprite :public Node{
	public:
		//static Sprite* create(const std::string& filename);
	};
	

	namespace StringUtils {
		int format(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
	};

	namespace utils {
		double gettime();
	};
	
	class Touch {
	public:
		Vec2 getLocation() const;
	};

}

class Ship {
public:
	int getShipId()const;
	int getIndex() const;
	int getCid()const;
	int getSkinCid()const;
	int getHP(void)const;
	int getHPMax(void)const;
};

class FightScene {
public:
	Ship*getShipByCid(int cid);
};


class UserManager {
public:
	struct FleetInfo {
		int index;
		int unknown1;
		int status;
		int unknown2;
		int*shipStartPtr;
		int*shipEndPtr;
	};
	struct UserShipData {
		int unknown1;
		int unknown2;
		int cid;
	};
public:
	static UserManager*getInstance();
	FleetInfo getIndexFleetInfo(int);
	UserShipData*getIndexUserShip(int);
	int getServerTime();

	static UserShipData*getFlagShip() {
		auto i = getInstance();
		if (i == nullptr) return nullptr;
		auto const& fi = i->getIndexFleetInfo(1);
		if (fi.shipStartPtr == nullptr || fi.shipStartPtr >= fi.shipEndPtr) return nullptr;
		auto id = *fi.shipStartPtr;
		return i->getIndexUserShip(id);
	}
};
class PveManager {
public:
	static PveManager*getInstance();
};