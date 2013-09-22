#include "../../../enemies/eato.h"
#include "../../../level/level.h"
#include "../../../core/sprite_manager.h"
#include "../../../core/property_helper.h"
#include "mrb_enemy.h"
#include "mrb_eato.h"

using namespace SMC;
using namespace SMC::Scripting;

// Extern
struct RClass* SMC::Scripting::p_rcEato = NULL;

/**
 * Method: Eato::new
 *
 *   new() → an_eato
 *
 * TODO: Docs.
 */
static mrb_value Initialize(mrb_state* p_state,  mrb_value self)
{
	cEato* p_eato = new cEato(pActive_Level->m_sprite_manager);
	DATA_PTR(self) = p_eato;
	DATA_TYPE(self) = &rtSMC_Scriptable;

	// This is a generated object
	p_eato->Set_Spawned(true);

	// Let SMC manage the memory
	pActive_Level->m_sprite_manager->Add(p_eato);

	return self;
}

/**
 * Method: Eato#image_dir=
 *
 *   image_dir=( path ) → path
 *
 * TODO: Docs.
 */
static mrb_value Set_Image_Dir(mrb_state* p_state, mrb_value self)
{
	char* cdir = NULL;
	mrb_get_args(p_state, "z", &cdir);

	cEato* p_eato = Get_Data_Ptr<cEato>(p_state, self);
	p_eato->Set_Image_Dir(utf8_to_path(cdir));

	return mrb_str_new_cstr(p_state, cdir);
}

/**
 * Method: Eato#image_dir
 *
 *   image_dir() → a_string
 *
 * TODO: Docs.
 */
static mrb_value Get_Image_Dir(mrb_state* p_state,  mrb_value self)
{
	cEato* p_eato = Get_Data_Ptr<cEato>(p_state, self);
	return mrb_str_new_cstr(p_state, path_to_utf8(p_eato->m_img_dir).c_str());
}

void SMC::Scripting::Init_Eato(mrb_state* p_state)
{
	p_rcEato = mrb_define_class(p_state, "Eato", p_rcEnemy);
	MRB_SET_INSTANCE_TT(p_rcEato, MRB_TT_DATA);

	mrb_define_method(p_state, p_rcEato, "initialize", Initialize, ARGS_REQ(1));
	mrb_define_method(p_state, p_rcEato, "image_dir", Get_Image_Dir, ARGS_NONE());
	mrb_define_method(p_state, p_rcEato, "image_dir=", Set_Image_Dir, ARGS_REQ(1));
}
