// #include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
// #include "C:/Wichtig/System/Static/Library/Victor2.h"
// #include "C:/Wichtig/System/Static/Library/Vdctor2.h"
// #include "C:/Wichtig/System/Static/Library/Complex.h"
// #include "C:/Wichtig/System/Static/Library/TransformedView.h"
// #include "C:\Wichtig\System\Static\Container\Vector.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Container/Vector.h"
#include "/home/codeleaded/System/Static/Container/Tree.h"


#define TILESIZE	64
#define OFFSET		0.5f

typedef struct MenuOption {
	long id;
	char* text;
} MenuOption;

MenuOption MenuOption_New(long id,char* text){
	MenuOption mo;
	mo.id = id;
	mo.text = CStr_Cpy(text);
	return mo;
}
void MenuOption_Free(MenuOption* mo){
	CStr_Free(&mo->text);
}
void MenuOption_Print(MenuOption* mo){
	printf(">>%ld : %s\n",mo->id,mo->text);
}


int Menu_X = 100;
int Menu_Y = 200;

Sprite Menu_Pointer;
Sprite Menu_Grapper;
Sprite Menu_Fold;
Sprite Menu_Atlas;

Vector trace;
MenuOption* selected;
Tree menu;

char Menu_enter(){
	Branch* b = Tree_Get_Branch(&menu,trace.size,trace.Memory);
	return b->Childs.size>0;
}
int Menu_Count(){
	Branch* b = Tree_Get_Branch(&menu,trace.size - 1,trace.Memory);
	return b->Childs.size;
}
int Menu_MaxLength(int Layers){
	Branch* b = Tree_Get_Branch(&menu,Layers,trace.Memory);
	
	int text_max = 0;

	for(int i = 0;i<b->Childs.size;i++){
		Branch* child = *(Branch**)Vector_Get(&b->Childs,i);
		MenuOption* mo = (MenuOption*)child->Memory;
		
		if(mo && mo->text){
			int text_new = CStr_Size(mo->text);
			if(text_new > text_max) text_max = text_new;
		}
	}
	
	return text_max;
}

void Menu_RenderLine(int Layers,int index){
	Branch* b = Tree_Get_Branch(&menu,Layers,trace.Memory);
	Branch* child = *(Branch**)Vector_Get(&b->Childs,index);
	MenuOption* mo = (MenuOption*)child->Memory;

	int length = Menu_MaxLength(Layers) + 1;
	float x = Menu_X + TILESIZE * OFFSET * Layers;
	float y = Menu_Y + index * TILESIZE + TILESIZE * OFFSET * Layers;

	Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x,y,0.0f,TILESIZE,TILESIZE,TILESIZE);
	Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x + length * TILESIZE,y,TILESIZE * 2.0f,TILESIZE,TILESIZE,TILESIZE);

	if(child->Childs.size>0)
		Sprite_RenderAlpha(WINDOW_STD_ARGS,&Menu_Fold,x,y);

	for(int i = 1;i<length;i++){
		Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x + i * TILESIZE,y,TILESIZE,TILESIZE,TILESIZE,TILESIZE);
	}

	if(mo && mo->text)
		RenderCStr(mo->text,x + TILESIZE,y,RED);
}
void Menu_RenderPart(int Layers){
	Branch* b = Tree_Get_Branch(&menu,Layers,trace.Memory);
	
	int length = Menu_MaxLength(Layers) + 1;
	float x = Menu_X + TILESIZE * OFFSET * Layers;
	float y = Menu_Y + TILESIZE * OFFSET * Layers;

	Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x,y - TILESIZE,0.0f,0.0f,TILESIZE,TILESIZE);
	Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x + length * TILESIZE,y - TILESIZE,TILESIZE * 2.0f,0.0f,TILESIZE,TILESIZE);
	for(int i = 1;i<length;i++){
		Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x + i * TILESIZE,y - TILESIZE,TILESIZE,0.0f,TILESIZE,TILESIZE);
	}

	for(int i = 0;i<b->Childs.size;i++){
		Branch* child = *(Branch**)Vector_Get(&b->Childs,i);
		//if(child && child->Memory) printf(">> %ld %s\n",((MenuOption*)child->Memory)->id,((MenuOption*)child->Memory)->text);
		Menu_RenderLine(Layers,i);
	}

	Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x,y + TILESIZE * (b->Childs.size),0.0f,TILESIZE * 2.0f,TILESIZE,TILESIZE);
	Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x + length * TILESIZE,y + TILESIZE * (b->Childs.size),TILESIZE * 2.0f,TILESIZE * 2.0f,TILESIZE,TILESIZE);
	for(int i = 1;i<length;i++){
		Sprite_RenderSubAlpha(WINDOW_STD_ARGS,&Menu_Atlas,x + i * TILESIZE,y + TILESIZE * (b->Childs.size),TILESIZE,TILESIZE * 2.0f,TILESIZE,TILESIZE);
	}
}


void Setup(AlxWindow* w){
	Menu_Pointer = Sprite_Load("./assets/Pointer.png");
	Menu_Grapper = Sprite_Load("./assets/Grapper.png");
	Menu_Fold = Sprite_Load("./assets/Fold.png");
	Menu_Atlas = Sprite_Load("./assets/Flowers_Atlas.png");

	Sprite_Resize(&Menu_Pointer,TILESIZE,TILESIZE / 2);
	Sprite_Resize(&Menu_Grapper,TILESIZE,TILESIZE / 2);
	Sprite_Resize(&Menu_Fold,TILESIZE,TILESIZE);
	Sprite_Resize(&Menu_Atlas,TILESIZE * 3,TILESIZE * 3);

	AlxFont_Resize(GetAlxFont(),TILESIZE,TILESIZE);

	trace = Vector_New(sizeof(int));
	menu = Tree_New();

	Tree_Add(&menu,0,(int[]){   },(MenuOption[]){ MenuOption_New(0,"magic") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 0 },(MenuOption[]){ MenuOption_New(1,"potions") },sizeof(MenuOption));
	Tree_Add(&menu,2,(int[]){ 0,0 },(MenuOption[]){ MenuOption_New(2,"heal") },sizeof(MenuOption));
	Tree_Add(&menu,2,(int[]){ 0,0 },(MenuOption[]){ MenuOption_New(3,"damage") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 0 },(MenuOption[]){ MenuOption_New(4,"iceball") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 0 },(MenuOption[]){ MenuOption_New(5,"lightning") },sizeof(MenuOption));

	Tree_Add(&menu,0,(int[]){   },(MenuOption[]){ MenuOption_New(6,"arrows") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 1 },(MenuOption[]){ MenuOption_New(7,"small") },sizeof(MenuOption));
	Tree_Add(&menu,2,(int[]){ 1,0 },(MenuOption[]){ MenuOption_New(8,"invisible") },sizeof(MenuOption));
	Tree_Add(&menu,2,(int[]){ 1,0 },(MenuOption[]){ MenuOption_New(9,"fast") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 1 },(MenuOption[]){ MenuOption_New(10,"big") },sizeof(MenuOption));
	Tree_Add(&menu,2,(int[]){ 1,1 },(MenuOption[]){ MenuOption_New(11,"invisible") },sizeof(MenuOption));
	Tree_Add(&menu,2,(int[]){ 1,1 },(MenuOption[]){ MenuOption_New(12,"fast") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 1 },(MenuOption[]){ MenuOption_New(13,"lightningarrow") },sizeof(MenuOption));

	Tree_Add(&menu,0,(int[]){   },(MenuOption[]){ MenuOption_New(14,"swords") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 2 },(MenuOption[]){ MenuOption_New(15,"fireswords") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 2 },(MenuOption[]){ MenuOption_New(16,"iceswords") },sizeof(MenuOption));
	Tree_Add(&menu,1,(int[]){ 2 },(MenuOption[]){ MenuOption_New(17,"lightningswords") },sizeof(MenuOption));

	Vector_Push(&trace,(int[]){ 0 });

	selected = NULL;
}
void Update(AlxWindow* w){
	if(Stroke(ALX_KEY_ENTER).PRESSED){
		if(trace.size > 0){
			selected = Tree_Get(&menu,trace.size,trace.Memory);
		}
	}
	
	if(Stroke(ALX_KEY_UP).PRESSED){
		if(trace.size > 0){
			int* last_trace = (int*)Vector_Get(&trace,trace.size - 1);
			if(*last_trace > 0) *last_trace -= 1;
		}
	}
	if(Stroke(ALX_KEY_DOWN).PRESSED){
		if(trace.size > 0){
			int* last_trace = (int*)Vector_Get(&trace,trace.size - 1);
			if(*last_trace < Menu_Count() - 1) *last_trace += 1;
		}
	}
	if(Stroke(ALX_KEY_LEFT).PRESSED){
		if(trace.size>0) Vector_PopTop(&trace);
	}
	if(Stroke(ALX_KEY_RIGHT).PRESSED){
		if(Menu_enter()) Vector_Push(&trace,(int[]){ 0 });
	}

	Clear(WHITE);

	for(int i = 0;i<trace.size;i++){
		int trace_in = *(int*)Vector_Get(&trace,i);
		Menu_RenderPart(i);
	}

	if(trace.size>0)
		Sprite_RenderAlpha(WINDOW_STD_ARGS,&Menu_Pointer,Menu_X - Menu_Pointer.w + TILESIZE * OFFSET * (trace.size - 1),Menu_Y + 0.5f * TILESIZE + (*(int*)Vector_Get(&trace,trace.size - 1)) * TILESIZE + TILESIZE * OFFSET * (trace.size - 1));
	
	//Sprite_RenderAlpha(WINDOW_STD_ARGS,&Menu_Grapper,TILESIZE,0.0f);

	if(selected && selected->text)
		RenderCStr(selected->text,0.0f,0.0f,BLUE);
}
void Delete(AlxWindow* w){
    Sprite_Free(&Menu_Pointer);
	Sprite_Free(&Menu_Grapper);
	Sprite_Free(&Menu_Fold);
	Sprite_Free(&Menu_Atlas);

	Vector_Free(&trace);

	Tree_ForEach(&menu,(void*)MenuOption_Free);
	Tree_Free(&menu);
}

int main(){
    if(Create("Menu System",1200,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}