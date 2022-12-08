#ifndef pack_packer_manager_h__
#define pack_packer_manager_h__

#include "libxpack.h"
#include <atomic>
#include <map>
#include <vector>
#include <mutex>

class Packer;
class PackerManager
{
/********************singleton begin**********************/
public:
	static PackerManager* getInstance();
private:
	static std::atomic<PackerManager*> instance;
	PackerManager();
	~PackerManager();
/********************singleton end**********************/

public:
	packer_t createPacker(size_t buf_size);
	bool destroyPacker(packer_t id);
	Packer* getPacker(packer_t id);

private:
	packer_t _getFreePackerId();
	void _freePackerId(packer_t id);

	std::map<packer_t, Packer*> _packerMap;
	std::vector<packer_t> _freePackerVec;
	packer_t _packerIdMax;

	std::mutex _pkMapLock;
};

#endif // pack_packer_manager_h__