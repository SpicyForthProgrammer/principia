//
// Copyright (c) 2013 Li-Cheng (Andy) Tai
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#include <gtest/gtest.h>
#include <sqrat.h>
#include "Fixture.h"


using namespace Sqrat;


class Entity 
{
public:
    Entity *FindEntity() { return NULL ; }
    
};


static const SQChar *sq_code = _SC("\
    local entity = Entity(); \
    gTest.EXPECT_FALSE(entity == null); \
    entity = entity.FindEntity(); \
    gTest.EXPECT_TRUE(entity == null); \
       ");



TEST_F(SqratTest, NullPointerReturn) {
    DefaultVM::Set(vm);
    
    Class<Entity> entity;
    entity.Func(_SC("FindEntity"), &Entity::FindEntity);
    RootTable().Bind(_SC("Entity"), entity);
        
    Script script;
    try {
        script.CompileString(sq_code);
    } catch(Exception ex) {
        FAIL() << _SC("Compile Failed: ") << ex.Message();
    }

    try {
        script.Run();
    } catch(Exception ex) {
        FAIL() << _SC("Run Failed: ") << ex.Message();
    }

}
