package com.my.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.my.game.ResourceStorage.ResourceManager;
import com.my.game.Screen.GameScreenManager;
import com.my.game.Screen.LoadState;

public class MyGame extends ApplicationAdapter {

    public static final int V_WIDTH = 800;
    public static final int V_HEIGHT = 480;
    public static float SCALE;

    public static final String TITLE = "Tanks";

    private GameScreenManager gsm;
    private SpriteBatch batch;
    ResourceManager resources;

    public MyGame(){}

    @Override
    public void create () {
        batch = new SpriteBatch();
        gsm = new GameScreenManager();
        resources = new ResourceManager();
        SCALE = Gdx.graphics.getWidth() / V_WIDTH;

        Gdx.gl.glClearColor(0, 0, 0, 1);
        Gdx.input.setCatchBackKey(true);

        gsm.push(new LoadState(gsm, resources));
    }

    @Override
    public void pause() {
        gsm.pause();
        super.pause();
    }

    @Override
    public void render () {

        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        gsm.update(Gdx.graphics.getDeltaTime());
        gsm.render(batch);
    }

    @Override
    public void dispose() {
        super.dispose();
        gsm.dispose();
        batch.dispose();
    }
}
