drop table if exists NonPlayerCharacter;
drop table if exists NonPlayerCharacterPath;
drop table if exists MapObjectType;
drop table if exists MapObject;
drop table if exists Container;
drop table if exists Hardpoints;
drop table if exists Interactionpoints;
drop table if exists Tiles;
drop table if exists Interaction;
drop table if exists Animation;
drop table if exists SpriteSheet;
drop table if exists Drawable;
drop table if exists Inventory;
drop table if exists InventoryHasItem;
drop table if exists Item;
drop table if exists Dialog;

create table NonPlayerCharacter
(
   MapObjectId integer(10) not null,
   speed integer(10) null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table NonPlayerCharacterPath
(
   MapObjectId integer(10) not null,
   WC_X integer(10) not null,
   WC_Y integer(10) not null,
   PathIndex integer(10) not null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table MapObjectType
(
   MapObjectTypeId integer primary key,
   TypeName varchar(50) not null,
   DrawableName varchar(50) not null,
   foreign key (DrawableName) references Drawable(DrawableName)
);

create table MapObject
(
   MapObjectId integer primary key,
   WC_X integer(10) null,
   WC_Y integer(10) null,
   BoundingBoxX integer(10) null,
   BoundingBoxY integer(10) null,
   MapObjectTypeId integer(10) not null,
   foreign key (MapObjectTypeId) references MapObjectType(MapObjecTypeId)
);

create table Container
(
   MapObjectId integer(10) not null,
   InventoryId integer(10) not null,
   foreign key(MapObjectId) references MapObject(MapObjectId),
   foreign key(InventoryId) references Inventory(InventoryId)
);

create table Hardpoints
(
   MapObjectTypeId integer(10) not null,
   RelativeX integer(10) not null,
   RelativeY integer(10) not null,
   HardpointType integer(10) not null,
   Width integer(10) null,
   Height integer(10) null,
   Radius integer(10) null,
   primary key (MapObjectTypeId, RelativeX, RelativeY, HardpointType),
   foreign key (MapObjectTypeId) references MapObjectType(MapObjectTypeId)
);

create table Interactionpoints
(
   MapObjectTypeId integer(10) not null,
   RelativeX integer(10) not null,
   RelativeY integer(10) not null,
   InteractionpointType integer(1) not null,
   Width integer(10) null,
   Height integer(10) null,
   Radius integer(10) null,
   RequiresMouseClick boolean null,
   primary key (MapObjectTypeId, RelativeX, RelativeY, InteractionpointType),
   foreign key (MapObjectTypeId) references MapObjectType(MapObjectTypeId)
);

create table Tiles
(
   MapObjectId integer(10) not null,
   TileType integer(10) null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table Interaction
(
   InteractionId integer(10) not null,
   MapObjectId integer(10) not null,
   Priority integer(3) not null,
   IsHandledOnce boolean not null,
   InteractionType integer(1) not null,
   AnimationName varchar(100),
   ItemId integer,
   Text varchar(1000),
   foreign key(MapObjectId) references MapObject(MapObjectId),
   foreign key(AnimationName) references Animation(AnimationName),
   foreign key(ItemId) references Item(ItemId),
);

create table Animation
(
   AnimationName varchar(100) not null,
   SpriteSheetName varchar(50) not null,
   Height integer(5) not null,
   Width integer(5) not null,
   StillsPerSecond integer(2) not null,
   primary key(AnimationName),
   foreign key(SpriteSheetName) references SpriteSheet(SpriteSheetName)
);

create table SpriteSheet
(
   SpriteSheetName varchar(50) not null,
   NumColumns integer(2) not null,
   NumRows integer(2) not null,
   primary key(SpriteSheetName)
);

create table Drawable
(
   DrawableName varchar(50) not null,
   AnimationName varchar(100) not null,
   foreign key(AnimationName) references Animation(AnimationName)
);

create table Inventory
(
    InventoryId integer primary key
);

create table InventoryHasItem
(
   InventoryId integer(10) not null,
   ItemId integer(10) not null,
   Quantity integer(10) not null,
   foreign key(ItemId) references Item(ItemId),
   foreign key(InventoryId) references Inventory(InventoryId)
);

create table Item
(
    ItemId integer primary key,
    ItemName varchar(50) not null
);

/* TEMPORARY Prototype for testing */
create table Dialog
(
   DialogId integer primary key not null,
   Quote varchar(1000) not null
);
