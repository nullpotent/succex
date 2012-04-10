#include "BaseGameEntity.h"

BaseGameEntity::BaseGameEntity(int entType) : id_(GetNextValidID()),
                                            boundingRadius_(0.0),
                                            position_(Vector2D()),
                                            scale_(Vector2D(1.0,1.0)),
                                            entityType_(entType),
                                            tag_(false)
{
}

BaseGameEntity::BaseGameEntity() : id_(GetNextValidID()),
                                   boundingRadius_(0.0),
                                   position_(Vector2D()),
                                   scale_(Vector2D(1.0,1.0)),
                                   entityType_(default_ent_type),
                                   tag_(false)
{
}

BaseGameEntity::BaseGameEntity(int entType, Vector2D pos, double r) : position_(pos),
                                                                      boundingRadius_(r),
                                                                      id_(GetNextValidID()),
                                                                      scale_(Vector2D(1.0,1.0)),
                                                                      entityType_(entType),
                                                                      tag_(false)
{
}

BaseGameEntity::BaseGameEntity(int entType, int forcedID) : id_(forcedID),
                                                            boundingRadius_(0.0),
                                                            position_(Vector2D()),
                                                            scale_(Vector2D(1.0,1.0)),
                                                            entityType_(entType),
                                                            tag_(false)
{
}
