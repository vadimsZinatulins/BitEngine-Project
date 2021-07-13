#ifndef __TEXTURE_RENDER_SYSTEM_H__
#define __TEXTURE_RENDER_SYSTEM_H__

#include "../Components/Texture.h"
#include "../Components/Position.h"
#include "../Components/Dimension.h"

#include <BitEngine/System.h>

struct TextureRenderSystem final : public BE::System<Texture, Position, Dimension>
{
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;
};

#endif // !__TEXTURE_RENDER_SYSTEM_H__
