// #include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
// #include "C:/Wichtig/System/Static/Library/Victor2.h"
// #include "C:/Wichtig/System/Static/Library/Vdctor2.h"
// #include "C:/Wichtig/System/Static/Library/Complex.h"
// #include "C:/Wichtig/System/Static/Library/TransformedView.h"
// #include "C:\Wichtig\System\Static\Container\Vector.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/MenuSystem.h"

MenuSystem menu;
MenuOption* selected;

void Setup(AlxWindow* w){
	menu = MenuSystem_New(
		"./assets/Pointer.png",
		"./assets/Fold.png",
		"./assets/FoldUp.png",
		"./assets/FoldDown.png",
		"./assets/Rainbow_Atlas.png",
		64,0.5f
	);

	MenuSystem_Set(&menu,0,(int[]){   },	MenuOption_New(0,"root"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(0,"magic"));
	MenuSystem_Add(&menu,1,(int[]){ 0 },	MenuOption_New(1,"potions"));
	MenuSystem_Add(&menu,2,(int[]){ 0,0 },	MenuOption_New(2,"heal"));
	MenuSystem_Add(&menu,2,(int[]){ 0,0 },	MenuOption_New(3,"damage"));
	MenuSystem_Add(&menu,1,(int[]){ 0 },	MenuOption_New(4,"iceball"));
	MenuSystem_Add(&menu,1,(int[]){ 0 },	MenuOption_New(5,"lightning"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(6,"arrows"));
	MenuSystem_Add(&menu,1,(int[]){ 1 },	MenuOption_New(7,"small"));
	MenuSystem_Add(&menu,2,(int[]){ 1,0 },	MenuOption_New(8,"invisible"));
	MenuSystem_Add(&menu,2,(int[]){ 1,0 },	MenuOption_New(9,"fast"));
	MenuSystem_Add(&menu,1,(int[]){ 1 },	MenuOption_New(10,"big"));
	MenuSystem_Add(&menu,2,(int[]){ 1,1 },	MenuOption_New(11,"invisible"));
	MenuSystem_Add(&menu,2,(int[]){ 1,1 },	MenuOption_New(12,"fast"));
	MenuSystem_Add(&menu,1,(int[]){ 1 },	MenuOption_New(13,"lightningarrow"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(14,"swords"));
	MenuSystem_Add(&menu,1,(int[]){ 2 },	MenuOption_New(15,"fireswords"));
	MenuSystem_Add(&menu,1,(int[]){ 2 },	MenuOption_New(16,"iceswords"));
	MenuSystem_Add(&menu,1,(int[]){ 2 },	MenuOption_New(17,"lightningswords"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(18,"dummy1"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(19,"dummy2"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(20,"dummy3"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(21,"dummy4"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(22,"dummy5"));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(23,"dummy6"));

	Menu_Option_Step(&menu);

	selected = NULL;
}
void Update(AlxWindow* w){
	if(Stroke(ALX_KEY_ENTER).PRESSED){
		selected = Menu_Option_Select(&menu);
	}
	if(Stroke(ALX_KEY_SPACE).PRESSED){
		MenuSystem_Deactivate(&menu,&menu.trace);
	}
	
	if(Stroke(ALX_KEY_UP).PRESSED){
		Menu_Option_Up(&menu);
	}
	if(Stroke(ALX_KEY_DOWN).PRESSED){
		Menu_Option_Down(&menu);
	}
	if(Stroke(ALX_KEY_LEFT).PRESSED){
		Menu_Option_Left(&menu);
	}
	if(Stroke(ALX_KEY_RIGHT).PRESSED){
		Menu_Option_Right(&menu);
	}

	Clear(WHITE);
	
	MenuSystem_Render(WINDOW_STD_ARGS,&menu,100.0f,200.0f);

	if(selected && selected->text)
		RenderCStr(selected->text,0.0f,0.0f,BLUE);
}
void Delete(AlxWindow* w){
    MenuSystem_Free(&menu);
}

int main(){
    if(Create("Menu System",2200,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}