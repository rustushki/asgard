--Tropical Island Demo

--Palm Tree MapObjectType (id = 1)
insert into MapObjectType
(MapObjectTypeId, TypeName, DrawableName)
values(1, "Palm Tree", "PalmTree");

--Rock MapObjectType (id = 2)
insert into MapObjectType
(MapObjectTypeId, TypeName, DrawableName)
values(2, "Rock", "Rock");

--Treasure Chest MapObjectType (id = 3)
insert into MapObjectType
(MapObjectTypeId, TypeName, DrawableName)
values(3, "Treasure Chest", "TreasureChest");

--Osiris Cat MapObjectType (id = 4)
insert into MapObjectType
(MapObjectTypeId, TypeName, DrawableName)
values(4, "Osiris Cat", "OsirisCat");

--Palm Tree 1 (id = 1)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,3,175,1);

--Treasure Chest (id = 2)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,40,40,3);

-- OsirisCat (id = 3)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,100,500,4);

--Palm Tree 2 (id = 4)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,1300,250,1);

--Palm Tree 3 (id = 5)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,1100,500,1);

--Palm Tree 4 (id = 6)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,1050,1100,1);

--Palm Tree 5 (id = 7)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,700,1217,1);

--Treasure Chest 1 (id = 8)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(1000,700,400,3);

--Treasure Chest 2 (id = 9)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,1200,500,3);

--Rock 1 (id = 10)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,250,250,2);

--Rock 2 (id = 11)
insert into MapObject
(MapObjectId,WC_X,WC_Y,MapObjectTypeId)
values(NULL,550,150,2);

--Palm Tree Hardpoints
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,47,224,14,8); --Rect
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,61,219,7,15); --Rect
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,63,205,7,15); --Rect
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,67,192,20,39); --Rect
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(1,0,85,222,10,14); --Rect
--End Palm Tree's Hardpoints

--Rock's Hardpoint
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,18,51,11);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,13,63,9);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,22,67,15);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,34,70,9);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,46,67,9);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,65,72,16);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,71,81,12);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,121,80,12);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(2,1,128,70,12);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(2,0,72,77,48,17);
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(2,0,16,39,125,21);
--End Rock's Hardpoints

--Treasure Chest's Hardpoint
--Hardpoint Type = 0 = RectHardPoint
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Width,Height)
values(3,0,6,31,62,20);
--End Treasure Chest's Hardpoint

--Osiris Cat's Hardpoints
insert into Hardpoints
(MapObjectTypeId,HardpointType,RelativeX,RelativeY,Radius)
values(4,1,15,19,6);
--End Osiris Cat's Hardpoints

insert into Drawable
(DrawableName,AnimationName)
values("PalmTree","PalmTree");

insert into Drawable
(DrawableName,AnimationName)
values("OsirisCat","OsirisCat");

insert into Drawable
(DrawableName,AnimationName)
values("TreasureChest","TreasureChest");

insert into Drawable
(DrawableName,AnimationName)
values("OsirisCat","OsirisCat");

insert into Drawable
(DrawableName,AnimationName)
values("Rock","Rock");

insert into Drawable
(DrawableName,AnimationName)
values("NotMatch","NotMatch");

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordSouth.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordNorth.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordEast.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("HandSwingsSwordWest.bmp",2,2);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("OsirisCat.png",3,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("palmtree.png",11,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("treasurechest.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("rock.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchStandingEast.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchStandingWest.png",1,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchWalkingWest.png",7,1);

insert into SpriteSheet
(SpriteSheetName,NumColumns,NumRows)
values("NotMatchWalkingEast.png",7,1);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("PalmTree","palmtree.png",240,170,6);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("OsirisCat","OsirisCat.png",75,25,5);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("TreasureChest","treasurechest.png",55,75,1);

insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("Rock","rock.png",96,145,1);

/** TEST:  Database load of Interactions **/
insert into Animation
(AnimationName,SpriteSheetName,Height,Width,StillsPerSecond)
values("TreasureChestOpening","treasurechest.png",55,75,1);

insert into Item
(ItemId,ItemName)
values(1,"Balloon Sword");

insert into Dialog
(DialogId,Quote)
values(1,"You found a...Balloon Sword?!?");

/* Item Interaction for Treasure Chest 1 */
insert into Interaction
(InteractionId,MapObjectId,Priority,InteractionType,AnimationName,ItemId,DialogId)
values(1,1000,1,1,NULL,1,NULL);

/* Animation Interaction for Treasure Chest 1 */
insert into Interaction
(InteractionId,MapObjectId,Priority,InteractionType,AnimationName,ItemId,DialogId)
values(2,1000,0,0,"TreasureChestOpening",NULL,NULL);

/* Dialog Interaction for Treasure Chest 1 */
insert into Interaction
(InteractionId,MapObjectId,Priority,InteractionType,AnimationName,ItemId,DialogId)
values(3,1000,2,2,NULL,NULL,1);

/** END TEST **/
