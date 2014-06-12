package com.soomla.cocos2dx.profile;

import android.app.Activity;
import android.util.Log;
import com.soomla.cocos2dx.common.DomainFactory;
import com.soomla.profile.SoomlaProfile;
import com.soomla.profile.domain.IProvider;
import com.soomla.profile.domain.UserProfile;
import com.soomla.profile.domain.rewards.Reward;
import com.soomla.profile.exceptions.ProviderNotFoundException;
import com.soomla.profile.exceptions.UserProfileNotFoundException;
import com.soomla.store.StoreUtils;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 5/24/13
 *         time 8:36 PM
 */
public class ProfileNdkGlue {

    private static final String TAG = "ProfileNdkGlue";

    private static WeakReference<Activity> mActivityRef = new WeakReference<Activity>(null);

    private static native void cppNativeCallHandler(String json);

    public static void sendMessageWithParameters(JSONObject paramList) {
        cppNativeCallHandler(paramList.toString());
    }

    public static void setActivity(Activity activity) {
        mActivityRef = new WeakReference<Activity>(activity);
    }

    @SuppressWarnings("UnusedDeclaration")
    public static String receiveCppMessage(String json) {
        if (json != null) {
            try {
                JSONObject params = new JSONObject(json);
                JSONObject retParamsJson = dispatchNDKCall(params);
                if (retParamsJson == null) {
                    retParamsJson = new JSONObject();
                }
                StoreUtils.LogDebug("ProfileNdkGlue", "retParamsJson: " + retParamsJson.toString());
                return retParamsJson.toString();
            } catch (JSONException e) {
                Log.e(TAG, "receiveCppMessage raised exception", e);
                StoreUtils.LogError("ProfileNdkGlue", "receiveCppMessage raised exception" + e);
            } catch (UnsupportedOperationException e) {
                Log.e(TAG, "", e);
                StoreUtils.LogError("ProfileNdkGlue", "Unsupported operation (" + e + ")");
            } catch (Exception e) {
                Log.e(TAG, "", e);
                StoreUtils.LogError("ProfileNdkGlue", "Unknown exception (" + e + ")");
            }
            return "{\"errorCode\": -4}";
        } else {
            return "{}";
        }
    }

    public static JSONObject dispatchNDKCall(JSONObject params) {
        JSONObject retParams = new JSONObject();
        try {
            try {
                String methodName = params.getString("method");
                if (methodName.equals("CCProfileController::init")) {
                    ProfileService.getInstance().init();
                }
                else if (methodName.equals("CCProfileController::login")) {
                    String provider = params.getString("provider");
                    JSONObject rewardJson = params.optJSONObject("reward");
                    Reward reward = (rewardJson != null) ?
                            DomainFactory.getInstance().<Reward>createWithJsonObject(rewardJson) : null;
                    SoomlaProfile.getInstance().login(mActivityRef.get(), IProvider.Provider.getEnum(provider), reward);
                } else if (methodName.equals("CCProfileController::logout")) {
                    String provider = params.getString("provider");
                    SoomlaProfile.getInstance().logout(IProvider.Provider.getEnum(provider));
                } else if (methodName.equals("CCProfileController::getStoredUserProfile")) {
                    String provider = params.getString("provider");
                    UserProfile userProfile = SoomlaProfile.getInstance().getStoredUserProfile(IProvider.Provider.getEnum(provider));
                    if (userProfile != null) {
                        retParams.put("return", userProfile.toJSONObject());
                    }
                } else if (methodName.equals("CCProfileController::updateStatus")) {
                    String provider = params.getString("provider");
                    String status = params.getString("status");
                    JSONObject rewardJson = params.optJSONObject("reward");
                    Reward reward = (rewardJson != null) ?
                            DomainFactory.getInstance().<Reward>createWithJsonObject(rewardJson) : null;
                    SoomlaProfile.getInstance().updateStatus(IProvider.Provider.getEnum(provider), status, reward);
                } else if (methodName.equals("CCProfileController::updateStory")) {
                    String provider = params.getString("provider");
                    String message = params.getString("message");
                    String name = params.getString("name");
                    String caption = params.getString("caption");
                    String description = params.getString("description");
                    String link = params.getString("link");
                    String picture = params.getString("picture");
                    JSONObject rewardJson = params.optJSONObject("reward");
                    Reward reward = (rewardJson != null) ?
                            DomainFactory.getInstance().<Reward>createWithJsonObject(rewardJson) : null;
                    SoomlaProfile.getInstance().updateStory(IProvider.Provider.getEnum(provider), message, name, caption,
                            description, link, picture, reward);
                } else if (methodName.equals("CCProfileController::uploadImage")) {
                    String provider = params.getString("provider");
                    String message = params.getString("message");
                    String filePath = params.getString("filePath");
                    JSONObject rewardJson = params.optJSONObject("reward");
                    Reward reward = (rewardJson != null) ?
                            DomainFactory.getInstance().<Reward>createWithJsonObject(rewardJson) : null;
                    SoomlaProfile.getInstance().uploadImage(IProvider.Provider.getEnum(provider), message, filePath,
                            reward);
                } else if (methodName.equals("CCProfileController::getContacts")) {
                    String provider = params.getString("provider");
                    JSONObject rewardJson = params.optJSONObject("reward");
                    Reward reward = (rewardJson != null) ?
                            DomainFactory.getInstance().<Reward>createWithJsonObject(rewardJson) : null;
                    SoomlaProfile.getInstance().getContacts(IProvider.Provider.getEnum(provider), reward);
                } else {
                    throw new UnsupportedOperationException(methodName);
                }
            } catch (ProviderNotFoundException e) {
                retParams.put("errorCode", -1);
            } catch (UserProfileNotFoundException e) {
                retParams.put("errorCode", -2);
            }
        } catch (JSONException e) {
            throw new IllegalArgumentException(e);
        }

        return retParams;
    }
}