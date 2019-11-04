package com.bugsnag.android;

import static com.bugsnag.android.BugsnagTestUtils.convert;
import static com.bugsnag.android.BugsnagTestUtils.generateConfiguration;
import static com.bugsnag.android.BugsnagTestUtils.mapToJson;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.anyLong;
import static org.mockito.Mockito.when;

import android.content.Context;
import android.content.pm.PackageManager;

import androidx.test.core.app.ApplicationProvider;

import org.json.JSONException;
import org.json.JSONObject;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.junit.MockitoJUnitRunner;

import java.util.Map;

@RunWith(MockitoJUnitRunner.class)
public class AppDataTest {

    private Map<String, Object> appData;

    @Mock
    SessionTracker sessionTracker;

    /**
     * Configures a new AppData for testing accessors + serialisation
     *
     */
    @Before
    public void setUp() {
        when(sessionTracker.isInForeground()).thenReturn(true);
        when(sessionTracker.getDurationInForegroundMs(anyLong())).thenReturn(500L);

        Context context = ApplicationProvider.getApplicationContext();
        PackageManager packageManager = context.getPackageManager();
        Configuration config = generateConfiguration();
        config.setVersionCode(1);
        AppData obj = new AppData(context, packageManager, convert(config),
                sessionTracker, NoopLogger.INSTANCE);
        this.appData = obj.getAppData();
    }

    @Test
    public void testAccessors() {
        assertEquals("com.bugsnag.android.core.test", appData.get("packageName"));
        assertNull(appData.get("buildUUID"));
        assertTrue(((Long) appData.get("duration")) >= 0);
        assertEquals(500L, appData.get("durationInForeground"));
        assertTrue((Boolean) appData.get("inForeground"));
    }
}
