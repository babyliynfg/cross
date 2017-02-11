#ifndef __CCGLPROGRAMSTATECACHE_H__
#define __CCGLPROGRAMSTATECACHE_H__

#include "ccTypes.h"
#include "basics/CASTLContainer.h"
#include "basics/CAPoint.h"
#include "basics/CAPoint3D.h"
#include "basics/CAVec4.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class GLProgram;

class GLProgramState;

/**
 Some GLprogram state could be shared. GLProgramStateCache is used to cache this, and will reuse the
 old GLProgramState, which will accelerate the creation of game objects such as sprites, particles etc.
 */
class CC_DLL GLProgramStateCache
{
public:
    /**Get the GLProgramStateCache singleton instance.*/
    static GLProgramStateCache* getInstance();
    /**Destroy the GLProgramStateCache singleton.*/
    static void destroyInstance();
    
    /**Get the shared GLProgramState by the owner GLProgram.*/
    GLProgramState* getGLProgramState(GLProgram* program);
    /**Remove all the cached GLProgramState.*/
	void removeAllGLProgramState();
    /**Remove unused GLProgramState.*/
    void removeUnusedGLProgramState();

protected:
    GLProgramStateCache();
    ~GLProgramStateCache();
    
    CAMap<GLProgram*, GLProgramState*> _glProgramStates;
    static GLProgramStateCache* s_instance;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif /* __CCGLPROGRAMSTATECACHE_H__ */
