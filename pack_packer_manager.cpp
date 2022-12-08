#include "pack_packer_manager.h"
#include "libxpack.h"
#include "pack_log.h"
#include "pack_packer.h"
#include <atomic>
#include <mutex>

std::atomic<PackerManager*> PackerManager::instance = nullptr;

PackerManager::PackerManager()
	:_packerIdMax(1) {
}

PackerManager::~PackerManager() {
}

packer_t PackerManager::createPacker(size_t buf_size) {
	std::lock_guard<std::mutex> l(_pkMapLock);

	Packer *packer = new Packer(buf_size);

	packer_t id = _getFreePackerId();
	_packerMap[id] = packer;

	return id;
}

bool PackerManager::destroyPacker(packer_t id) {
	std::lock_guard<std::mutex> l(_pkMapLock);

	if (_packerMap.count(id) == 0) {
		pack_log_error("id %d is not exsist", id);
		return false;
	}

	Packer* packer = _packerMap[id];
	delete packer;

	_packerMap.erase(id);
	_freePackerId(id);

	return true;
}

Packer* PackerManager::getPacker(packer_t id) {
	std::lock_guard<std::mutex> l(_pkMapLock);
	Packer* ret = nullptr;

	if (_packerMap.count(id) > 0) {
		ret = _packerMap[id];
	}
	return ret;
}

packer_t PackerManager::_getFreePackerId() {
	if (!_freePackerVec.empty()) {
		packer_t ret = _freePackerVec.back();
		_freePackerVec.pop_back();
		return ret;
	}
	return _packerIdMax++;
}

void PackerManager::_freePackerId(packer_t id) {
	_freePackerVec.push_back(id);
}

PackerManager* PackerManager::getInstance() {
	PackerManager* tmp = instance.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if (tmp == nullptr) {
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		tmp = instance.load(std::memory_order_relaxed);
		if (tmp == nullptr) {
			tmp = new PackerManager();
			std::atomic_thread_fence(std::memory_order_release);
			instance.store(tmp, std::memory_order_relaxed);
		}
	}
	return tmp;
}
