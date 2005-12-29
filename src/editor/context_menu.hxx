//  $Id: context_menu.hxx,v 1.00 2005/12/29 23:41:12 Jave27 Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_PINGUS_EDITOR_CONTEXT_MENU_HXX
#define HEADER_PINGUS_EDITOR_CONTEXT_MENU_HXX

#include <vector>
#include "../vector.hxx"
#include "../gui/component.hxx"

namespace Pingus {

namespace Editor {

	class LevelObj;
	class EditorViewport;

	class ContextMenu : public GUI::Component {
	private:
		/** Level objects to be affected by this menu */
		std::vector<LevelObj*> objs;

		/** Viewport to which this menu belongs */
		EditorViewport* viewport;

		/** List of actions available in this menu */
		std::vector<std::string> actions;

		/** Where the mouse is located */
		Vector mouse_at;

		/** Location of context menu */
		Vector pos;

		/** Is the mouse over the menu? */
		bool hover;

		/** The offset into actions vector of the currently highlighted action */
		unsigned selected_action_offset;

		/** Height of a single action */
		unsigned item_height;

		unsigned total_height;
		unsigned width;

	public:
		// Constructor
		ContextMenu (std::vector<LevelObj*>, Vector p, EditorViewport* v);
		
		// Desctructor
		~ContextMenu ();

		/// GUI Component Functions
		bool is_at(int x, int y);
		void draw (DrawingContext& gc);
		void on_pointer_move (int x, int y);
		void on_primary_button_click(int x, int y);
		void on_secondary_button_click(int x, int y);
		void on_pointer_enter () { hover = true; }
		void on_pointer_leave () { hover = false; }

	private:
		ContextMenu ();
		ContextMenu (const ContextMenu&);
	  ContextMenu& operator= (const ContextMenu&);

	};	// ContextMenu class

}	// Editor namespace
} // Pingus namespace

#endif

/* EOF */