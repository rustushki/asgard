drop table if exists NonPlayerCharacter;
drop table if exists NonPlayerCharacterPath;
drop table if exists BoundingBox;
drop table if exists MapObject;
drop table if exists Container;
drop table if exists Hardpoints;
drop table if exists Tiles;
drop table if exists Animation;
drop table if exists SpriteSheet;
drop table if exists Drawable;

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

create table BoundingBox
(
   BoundingBoxId integer primary key,
   WC_X integer(10) null,
   WC_Y integer(10) null,
   Height integer(10) null,
   Width integer(10) null
);

create table MapObject
(
   MapObjectId integer primary key,
   WC_X integer(10) null,
   WC_Y integer(10) null,
   Height integer(10) null,
   Width integer(10) null,
   BoundingBoxId integer(10) null,
   DrawableName varchar(50) not null,
   foreign key (DrawableName) references Drawable(DrawableName)
);

create table Container
(
   MapObjectId integer(10) null,
   item0 integer(10) null,
   item1 integer(10) null,
   item2 integer(10) null,
   item3 integer(10) null,
   item4 integer(10) null,
   item5 integer(10) null,
   item6 integer(10) null,
   item7 integer(10) null,
   item8 integer(10) null,
   item9 integer(10) null,
   item10 integer(10) null,
   item11 integer(10) null,
   item12 integer(10) null,
   item13 integer(10) null,
   item14 integer(10) null,
   foreign key(MapObjectId) references MapObject(MapObjectId)
);

create table Hardpoints
(
   MapObjectId integer(10) not null,
   RelativeX integer(10) not null,
   RelativeY integer(10) not null,
   HardpointType integer(10) not null,
   Width integer(10) null,
   Height integer(10) null,
   Radius integer(10) null,
   primary key (MapObjectId, RelativeX, RelativeY, HardpointType),
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table Tiles
(
   MapObjectId integer(10) not null,
   TileType integer(10) null,
   foreign key (MapObjectId) references MapObject(MapObjectId)
);

create table Animation
(
   AnimationName varchar(100) not null,
   SpriteSheetName varchar(50) not null,
   Height integer(5) not null,
   Width integer(5) not null,
   StillCount integer(2) not null,
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
