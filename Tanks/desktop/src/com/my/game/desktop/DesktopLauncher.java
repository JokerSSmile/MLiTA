package com.my.game.desktop;

import com.badlogic.gdx.Files;
import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.my.game.MyGame;

public class DesktopLauncher {
	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = MyGame.V_WIDTH;
		config.height = MyGame.V_HEIGHT;
		config.title = MyGame.TITLE;
		new LwjglApplication(new MyGame(), config);
	}
}