#ifndef OOP_MAP_MAP_H_
#define OOP_MAP_MAP_H_

#include <memory>

#include "../Cell/Cell.h"
#include "../Def.h"
#include "../Log/Loggable.h"
#include "../Render/Framebuffer.h"

class Map : public ILoggable, public Saveable {

public:
    Map(coord_t size);

    Map(const Map &other);

    Map &operator=(const Map &other);

    Map(Map &&other);

    Map &operator=(Map &&other);

    coord_t GetEnterCoord();

    coord_t GetExitCoord();

    coord_t GetSize();

    std::shared_ptr<Cell> &GetCellRef(const coord_t &coord);

    std::shared_ptr<Cell> GetCell(const coord_t &coord);

    static std::shared_ptr<Map> Load(std::ifstream &file);

    void Save(std::ofstream &file) override;

    void Init();

    void Draw(const std::shared_ptr<Framebuffer> &framebuffer);

    void SetLogger(const std::shared_ptr<ILogger> &logger) override;

private:
    void AllocCellsPointers(const coord_t &size);

    void Copy(const Map &other);

    void Move(Map &other);

    coord_t size_;
    coord_t enter_coord_, exit_coord_;
    std::unique_ptr<std::shared_ptr<Cell>[]> cells_;
};

#endif // OOP_MAP_MAP_H_

