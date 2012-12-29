/*****************************************************************************
 * Copyright (c) 2007 Russ Adams, Sean Eubanks, Asgard Contributors
 * This file is part of Asgard.
 * 
 * Asgard is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asgard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with Asgard; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/
 
#ifndef DATABASECOLUMNMAP_H
#define DATABASECOLUMNMAP_H
enum DatabaseQuery
{
   DATABASE_QUERY_MAP_OBJECT,
   DATABASE_QUERY_NON_PLAYER_CHARACTER,
   DATABASE_QUERY_NON_PLAYER_CHARACTER_PATH,
   DATABASE_QUERY_CONTAINER,
   DATABASE_QUERY_TILE,
   DATABASE_QUERY_HARDPOINT,
   DATABASE_QUERY_COUNT
};

enum MapObjectColumn
{
   MAP_OBJECT_COLUMN_MAP_OBJECT_ID,
   MAP_OBJECT_COLUMN_WC_X,
   MAP_OBJECT_COLUMN_WC_Y,
   MAP_OBJECT_COLUMN_DRAWABLE_NAME,
   MAP_OBJECT_COLUMN_COUNT
};

enum NonPlayerCharacterColumn
{
   NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID,
   NON_PLAYER_CHARACTER_COLUMN_WC_X,
   NON_PLAYER_CHARACTER_COLUMN_WC_Y,
   NON_PLAYER_CHARACTER_COLUMN_DRAWABLE_NAME,
   NON_PLAYER_CHARACTER_COLUMN_SPEED,
   NON_PLAYER_CHARACTER_COLUMN_COUNT
};

enum NonPlayerCharacterPathColumn
{
   NON_PLAYER_CHARACTER_PATH_COLUMN_MAP_OBJECT_ID,
   NON_PLAYER_CHARACTER_PATH_COLUMN_WC_X,
   NON_PLAYER_CHARACTER_PATH_COLUMN_WC_Y,
   NON_PLAYER_CHARACTER_PATH_COLUMN_PATHINDEX,
   NON_PLAYER_CHARACTER_PATH_COLUMN_COUNT
};

enum ContainerColumn
{
   CONTAINER_COLUMN_MAP_OBJECT_ID,
   CONTAINER_COLUMN_WC_X,
   CONTAINER_COLUMN_WC_Y,
   CONTAINER_COLUMN_DRAWABLE_NAME,
   CONTAINER_COLUMN_COUNT
};

enum TileColumn
{
   TILE_COLUMN_MAP_OBJECT_ID,
   TILE_COLUMN_WC_X,
   TILE_COLUMN_WC_Y,
   TILE_COLUMN_DRAWABLE_NAME,
   TILE_COLUMN_TILE_TYPE,
   TILE_COLUMN_COUNT
};

enum HardpointColumn
{
   HARDPOINT_COLUMN_MAP_OBJECT_ID,
   HARDPOINT_COLUMN_RELATIVE_X,
   HARDPOINT_COLUMN_RELATIVE_Y,
   HARDPOINT_COLUMN_HARDPOINT_TYPE,
   HARDPOINT_COLUMN_WIDTH,
   HARDPOINT_COLUMN_HEIGHT,
   HARDPOINT_COLUMN_RADIUS,
   HARDPOINT_COLUMN_COUNT
};

/* Default Interaction selection */
enum InteractionColumn
{
   INTERACTION_COLUMN_PRIORITY,
   INTERACTION_COLUMN_IS_HANDLED_ONCE,
   INTERACTION_COLUMN_COUNT
};

/* Interaction inner joined to Animation */
/* See QueryGenerator::animationInteraction() */
enum AnimationInteractionColumn
{
   ANIMATION_INTERACTION_COLUMN_PRIORITY,
   ANIMATION_INTERACTION_COLUMN_IS_HANDLED_ONCE,
   ANIMATION_INTERACTION_COLUMN_ANIMATION_NAME,
   ANIMATION_INTERACTION_COLUMN_COUNT
};

/* Interaction inner joined to Item */
/* See QueryGenerator::itemInteraction() */
enum ItemInteractionColumn
{
   ITEM_INTERACTION_COLUMN_PRIORITY,
   ITEM_INTERACTION_COLUMN_IS_HANDLED_ONCE,
   ITEM_INTERACTION_COLUMN_ITEM_NAME,
   ITEM_INTERACTION_COLUMN_COUNT
};

/* Interaction inner joined to Dialog */
/* See QueryGenerator::dialogInteraction() */
enum DialogInteractionColumn
{
   DIALOG_INTERACTION_COLUMN_PRIORITY,
   DIALOG_INTERACTION_COLUMN_IS_HANDLED_ONCE,
   DIALOG_INTERACTION_COLUMN_QUOTE,
   DIALOG_INTERACTION_COLUMN_COUNT
};

/* Animation inner joined to SpriteSheet inner joined to Drawable */
/* See QueryGenerator::drawable(std::string dName)                */

enum AnimationColumn
{
   ANIMATION_COLUMN_DRAWABLE_NAME,
   ANIMATION_COLUMN_ANIMATION_NAME,
   ANIMATION_COLUMN_SPRITE_SHEET_NAME,
   ANIMATION_COLUMN_SPRITE_SHEET_NUM_COLUMNS,
   ANIMATION_COLUMN_SPRITE_SHEET_NUM_ROWS,
   ANIMATION_COLUMN_HEIGHT,
   ANIMATION_COLUMN_WIDTH,
   ANIMATION_COLUMN_STILLS_PER_SECOND,
   ANIMATION_COLUMN_COUNT
};

enum SpriteSheetColumn
{
   SPRITE_SHEET_COLUMN_SPRITE_SHEET_NAME,
   SPRITE_SHEET_COLUMN_NUM_COLUMNS,
   SPRITE_SHEET_COLUMN_NUM_ROWS,
   SPRITE_SHEET_COLUMN_COUNT
};

enum DrawableColumn
{
   DRAWABLE_COLUMN_DRAWABLE_NAME,
   DRAWABLE_COLUMN_ANIMATION_NAME,
   DRAWABLE_COLUMN_COUNT
};
#endif//DATABASECOLUMNMAP_H
