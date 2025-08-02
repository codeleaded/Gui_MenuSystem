// #include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
// #include "C:/Wichtig/System/Static/Library/Victor2.h"
// #include "C:/Wichtig/System/Static/Library/Vdctor2.h"
// #include "C:/Wichtig/System/Static/Library/Complex.h"
// #include "C:/Wichtig/System/Static/Library/TransformedView.h"
// #include "C:\Wichtig\System\Static\Container\Vector.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/MenuSystem.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"

MenuSystem menu;
MenuOption* selected;

TransformedView tv;
Rect rect;
Vec2 velocity;
Vec2 acceleration;

void Setup(AlxWindow* w){
	menu = MenuSystem_New(
		"./assets/Pointer.png",
		"./assets/Fold.png",
		"./assets/FoldUp.png",
		"./assets/FoldDown.png",
		"./assets/Rainbow_Atlas.png",
		64,0.5f
	);

	/*
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
	*/

	MenuSystem_Set(&menu,0,(int[]){   },	MenuOption_New(0,"root","NONE",NULL,NULL));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(1,"position","(x,y)",NULL,NULL));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(2,"dimension","(x,y)",NULL,NULL));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(3,"velocity","(x,y)",NULL,NULL));
	MenuSystem_Add(&menu,0,(int[]){   },	MenuOption_New(4,"acceleration","(x,y)",NULL,NULL));
	MenuSystem_Add(&menu,1,(int[]){ 0 },	MenuOption_New(5,"x","0.0",&rect.p.x,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 0 },	MenuOption_New(6,"y","0.0",&rect.p.y,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 1 },	MenuOption_New(7,"x","1.0",&rect.d.x,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 1 },	MenuOption_New(8,"y","1.0",&rect.d.y,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 2 },	MenuOption_New(9,"x","0.0",&velocity.x,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 2 },	MenuOption_New(10,"y","0.0",&velocity.y,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 3 },	MenuOption_New(11,"x","0.0",&acceleration.x,(char *(*)(void*))Float_CStr));
	MenuSystem_Add(&menu,1,(int[]){ 3 },	MenuOption_New(12,"y","0.0",&acceleration.y,(char *(*)(void*))Float_CStr));

	MenuSystem_Option_Step(&menu);

	selected = NULL;


	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
	TransformedView_Offset(&tv,(Vec2){ 0.0f,0.0f });

	rect = (Rect){ 0.0f,0.0f,0.05f,0.05f };
	velocity = (Vec2){ 0.0f,0.0f };
	acceleration = (Vec2){ 0.0f,0.0f };
}
void Update(AlxWindow* w){
	tv.ZoomSpeed = (float)w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,(Vec2){ GetMouse().x,GetMouse().y });
	
	if(Stroke(ALX_KEY_ENTER).PRESSED){
		selected = MenuSystem_Option_Select(&menu);
	}
	if(Stroke(ALX_KEY_SPACE).PRESSED){
		MenuSystem_Deactivate(&menu,&menu.trace);
	}
	
	if(Stroke(ALX_KEY_UP).PRESSED){
		MenuSystem_Option_Up(&menu);
	}
	if(Stroke(ALX_KEY_DOWN).PRESSED){
		MenuSystem_Option_Down(&menu);
	}
	if(Stroke(ALX_KEY_LEFT).PRESSED){
		MenuSystem_Option_Left(&menu);
	}
	if(Stroke(ALX_KEY_RIGHT).PRESSED){
		MenuSystem_Option_Right(&menu);
	}

	if(Stroke(ALX_KEY_W).DOWN){
		MenuOption* select = MenuSystem_Option_Select(&menu);
		
		if(CStr_Cmp(select->text,"x") || CStr_Cmp(select->text,"y")){
			*((float*)select->data) += 0.1f * (float)w->ElapsedTime;
		}
	}
	if(Stroke(ALX_KEY_S).DOWN){
		MenuOption* select = MenuSystem_Option_Select(&menu);
		
		if(CStr_Cmp(select->text,"x") || CStr_Cmp(select->text,"y")){
			*((float*)select->data) -= 0.1f * (float)w->ElapsedTime;
		}
	}

	MenuSystem_Update(&menu);


	velocity = Vec2_Add(velocity,Vec2_Mulf(acceleration,w->ElapsedTime));
	rect.p = Vec2_Add(rect.p,Vec2_Mulf(velocity,w->ElapsedTime));

	if(rect.p.x<0.0f){
		rect.p.x = 0.0f;
		velocity.x *= -1.0f;
	}
	if(rect.p.y<0.0f){
		rect.p.y = 0.0f;
		velocity.y *= -1.0f;
	}
	if(rect.p.x>1.0f - rect.d.x){
		rect.p.x = 1.0f - rect.d.x;
		velocity.x *= -1.0f;
	}
	if(rect.p.y>1.0f - rect.d.y){
		rect.p.y = 1.0f - rect.d.y;
		velocity.y *= -1.0f;
	}



	Clear(WHITE);
	

	Vec2 bg_p = TransformedView_WorldScreenPos(&tv,(Vec2){ 0.0f,0.0f });
	Vec2 bg_d = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
	RenderRect(bg_p.x,bg_p.y,bg_d.x,bg_d.y,BLUE);

	Vec2 p = TransformedView_WorldScreenPos(&tv,rect.p);
	Vec2 d = TransformedView_WorldScreenLength(&tv,rect.d);
	RenderRect(p.x,p.y,d.x,d.y,RED);

	MenuSystem_Render(WINDOW_STD_ARGS,&menu,500.0f,850.0f);

	//if(selected && selected->text)
	//	RenderCStr(selected->text,0.0f,0.0f,BLUE);
}
void Delete(AlxWindow* w){
    MenuSystem_Free(&menu);
}

int main(){
    if(Create("Menu System",2200,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}