/*
 * Copyright (c) 2014, The CyanogenMod Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.internal.telephony;

import static com.android.internal.telephony.RILConstants.*;

import android.content.Context;
import android.telephony.Rlog;
import android.os.AsyncResult;
import android.os.Message;
import android.os.Parcel;
import android.os.SystemProperties;
import android.telephony.PhoneNumberUtils;
import android.telephony.SignalStrength;
import com.android.internal.telephony.uicc.IccCardApplicationStatus;
import com.android.internal.telephony.uicc.IccCardStatus;
import java.util.ArrayList;
import java.util.Collections;
import com.android.internal.telephony.uicc.IccUtils;

/**
 * Marvell RIL for Samsung PXA1908 Dual-sim devices
 * {@hide}
 */
public class SamsungPXA1908RIL extends RIL {
    private static final int RIL_REQUEST_10001 = 10001;
    private static final int RIL_UNSOL_11001   = 11001;

    public SamsungPXA1908RIL(Context context, int preferredNetworkType, int cdmaSubscription) {
        super(context, preferredNetworkType, cdmaSubscription, null);
        mQANElements = 6;
    }



    public SamsungPXA1908RIL(Context context, int preferredNetworkType,
            int cdmaSubscription, Integer instanceId) {
        super(context, preferredNetworkType, cdmaSubscription, instanceId);
        mQANElements = 6;
    }



    @Override
    public void
    dial(String address, int clirMode, UUSInfo uusInfo, Message result) {
        RILRequest rr = RILRequest.obtain(RIL_REQUEST_DIAL, result);
        rr.mParcel.writeString(address);
        rr.mParcel.writeInt(clirMode);
        rr.mParcel.writeInt(0);
        rr.mParcel.writeInt(1);
        rr.mParcel.writeString("");
        if (uusInfo == null) {
            rr.mParcel.writeInt(0);
        } else {
            rr.mParcel.writeInt(1);
            rr.mParcel.writeInt(uusInfo.getType());
            rr.mParcel.writeInt(uusInfo.getDcs());
            rr.mParcel.writeByteArray(uusInfo.getUserData());
        }
        riljLog(rr.serialString() + "> " + requestToString(rr.mRequest));
        send(rr);
    /*
        if (PhoneNumberUtils.isEmergencyNumber(address)) {
            dialEmergencyCall(address, clirMode, result);
            return;
        }

        RILRequest rr = RILRequest.obtain(RIL_REQUEST_DIAL, result);

        rr.mParcel.writeString(address);
        rr.mParcel.writeInt(clirMode);
        rr.mParcel.writeInt(0);     // CallDetails.call_type
        rr.mParcel.writeInt(1);     // CallDetails.call_domain
        rr.mParcel.writeString(""); // CallDetails.getCsvFromExtras

        if (uusInfo == null) {
            rr.mParcel.writeInt(0); // UUS information is absent
        } else {
            rr.mParcel.writeInt(1); // UUS information is present
            rr.mParcel.writeInt(uusInfo.getType());
            rr.mParcel.writeInt(uusInfo.getDcs());
            rr.mParcel.writeByteArray(uusInfo.getUserData());
        }

        if (RILJ_LOGD) riljLog(rr.serialString() + "> " + requestToString(rr.mRequest));

        send(rr);
        */
    }

    @Override
    protected Object
    responseIccCardStatus(Parcel p) {
        IccCardApplicationStatus appStatus;

        IccCardStatus cardStatus = new IccCardStatus();
        cardStatus.setCardState(p.readInt());
        cardStatus.setUniversalPinState(p.readInt());
        cardStatus.mGsmUmtsSubscriptionAppIndex = p.readInt();
        cardStatus.mCdmaSubscriptionAppIndex = p.readInt();
        cardStatus.mImsSubscriptionAppIndex = p.readInt();

        int numApplications = p.readInt();

        // limit to maximum allowed applications
        if (numApplications > IccCardStatus.CARD_MAX_APPS) {
            numApplications = IccCardStatus.CARD_MAX_APPS;
        }
        cardStatus.mApplications = new IccCardApplicationStatus[numApplications];

        for (int i = 0 ; i < numApplications ; i++) {
            appStatus = new IccCardApplicationStatus();
            appStatus.app_type       = appStatus.AppTypeFromRILInt(p.readInt());
            appStatus.app_state      = appStatus.AppStateFromRILInt(p.readInt());
            appStatus.perso_substate = appStatus.PersoSubstateFromRILInt(p.readInt());
            appStatus.aid            = p.readString();
            appStatus.app_label      = p.readString();
            appStatus.pin1_replaced  = p.readInt();
            appStatus.pin1           = appStatus.PinStateFromRILInt(p.readInt());
            appStatus.pin2           = appStatus.PinStateFromRILInt(p.readInt());
            p.readInt(); // pin1_num_retries
            p.readInt(); // puk1_num_retries
            p.readInt(); // pin2_num_retries
            p.readInt(); // puk2_num_retries
            p.readInt(); // perso_unblock_retries

            cardStatus.mApplications[i] = appStatus;
        }
        return cardStatus;

    }



    @Override
    protected Object
    responseCallList(Parcel p) {
        int num = p.readInt();
        ArrayList<DriverCall> response = new ArrayList(num);
        for (int i = 0; i < num; i++) {
            boolean z;
            DriverCall dc = new DriverCall();
            dc.state = DriverCall.stateFromCLCC(p.readInt());
            dc.index = p.readInt();
            //dc.id = (dc.index >> 8) & 255;
            dc.index &= 255;
            dc.TOA = p.readInt();
            dc.isMpty = p.readInt() != 0;
            dc.isMT = p.readInt() != 0;
            dc.als = p.readInt();
            if (p.readInt() == 0) {
                z = false;
            } else {
                z = true;
            }
            dc.isVoice = z;
            int type = p.readInt();
            int domain = p.readInt();
            String extras = p.readString();
            //dc.callDetails = new CallDetails(type, domain, null);
            //dc.callDetails.setExtrasFromCsv(extras);
            //Rlog.d(RILJ_LOG_TAG, "dc.index " + dc.index + " dc.id " + dc.id + " dc.callDetails " + dc.callDetails);
            dc.isVoicePrivacy = p.readInt() != 0;
            dc.number = p.readString();
            dc.numberPresentation = DriverCall.presentationFromCLIP(p.readInt());
            dc.name = p.readString();
            Rlog.d(RILJ_LOG_TAG, "responseCallList dc.name" + dc.name);
            dc.namePresentation = DriverCall.presentationFromCLIP(p.readInt());
            if (p.readInt() == 1) {
                dc.uusInfo = new UUSInfo();
                dc.uusInfo.setType(p.readInt());
                dc.uusInfo.setDcs(p.readInt());
                dc.uusInfo.setUserData(p.createByteArray());
                riljLogv(String.format("Incoming UUS : type=%d, dcs=%d, length=%d", new Object[]{Integer.valueOf(dc.uusInfo.getType()), Integer.valueOf(dc.uusInfo.getDcs()), Integer.valueOf(dc.uusInfo.getUserData().length)}));
                riljLogv("Incoming UUS : data (string)=" + new String(dc.uusInfo.getUserData()));
                riljLogv("Incoming UUS : data (hex): " + IccUtils.bytesToHexString(dc.uusInfo.getUserData()));
            } else {
                riljLogv("Incoming UUS : NOT present!");
            }
            dc.number = PhoneNumberUtils.stringFromStringAndTOA(dc.number, dc.TOA);
            response.add(dc);
            if (dc.isVoicePrivacy) {
                this.mVoicePrivacyOnRegistrants.notifyRegistrants();
                riljLog("InCall VoicePrivacy is enabled");
            } else {
                this.mVoicePrivacyOffRegistrants.notifyRegistrants();
                riljLog("InCall VoicePrivacy is disabled");
            }
        }
        Collections.sort(response);
        if (num == 0 && this.mTestingEmergencyCall.getAndSet(false) && this.mEmergencyCallbackModeRegistrant != null) {
            riljLog("responseCallList: call ended, testing emergency call, notify ECM Registrants");
            this.mEmergencyCallbackModeRegistrant.notifyRegistrant();
        }
        return response;
        /*
        int num;
        int voiceSettings;
        ArrayList<DriverCall> response;
        DriverCall dc;
        num = p.readInt();
        response = new ArrayList<DriverCall>(num);

        if (RILJ_LOGV) {
            riljLog("responseCallList: num=" + num +
                    " mEmergencyCallbackModeRegistrant=" + mEmergencyCallbackModeRegistrant +
                    " mTestingEmergencyCall=" + mTestingEmergencyCall.get());
        }

        for (int i = 0 ; i < num ; i++) {
            dc = new DriverCall();
            dc.state = DriverCall.stateFromCLCC(p.readInt());
            dc.index = p.readInt() & 0xff;
            dc.TOA = p.readInt();
            dc.isMpty = (0 != p.readInt());
            dc.isMT = (0 != p.readInt());
            dc.als = p.readInt();
            voiceSettings = p.readInt();
            dc.isVoice = (0 == voiceSettings) ? false : true;
            boolean isVideo;
            int call_type = p.readInt();            // Samsung CallDetails
            int call_domain = p.readInt();          // Samsung CallDetails
            String csv = p.readString();            // Samsung CallDetails
            dc.isVoicePrivacy = (0 != p.readInt());
            dc.number = p.readString();
            int np = p.readInt();
            dc.numberPresentation = DriverCall.presentationFromCLIP(np);
            dc.name = p.readString();
            dc.namePresentation = DriverCall.presentationFromCLIP(p.readInt());
            int uusInfoPresent = p.readInt();

            if (uusInfoPresent == 1) {
                dc.uusInfo = new UUSInfo();
                dc.uusInfo.setType(p.readInt());
                dc.uusInfo.setDcs(p.readInt());
                byte[] userData = p.createByteArray();
                dc.uusInfo.setUserData(userData);
                riljLogv(String.format("Incoming UUS : type=%d, dcs=%d, length=%d",
                                dc.uusInfo.getType(), dc.uusInfo.getDcs(),
                                dc.uusInfo.getUserData().length));
                riljLogv("Incoming UUS : data (string)="
                        + new String(dc.uusInfo.getUserData()));
                riljLogv("Incoming UUS : data (hex): "
                        + IccUtils.bytesToHexString(dc.uusInfo.getUserData()));
            } else {
                riljLogv("Incoming UUS : NOT present!");
            }

            // Make sure there's a leading + on addresses with a TOA of 145
            dc.number = PhoneNumberUtils.stringFromStringAndTOA(dc.number, dc.TOA);

            response.add(dc);

            if (dc.isVoicePrivacy) {
                mVoicePrivacyOnRegistrants.notifyRegistrants();
                riljLog("InCall VoicePrivacy is enabled");
            } else {
                mVoicePrivacyOffRegistrants.notifyRegistrants();
                riljLog("InCall VoicePrivacy is disabled");
            }
        }

        Collections.sort(response);

        if ((num == 0) && mTestingEmergencyCall.getAndSet(false)) {
            if (mEmergencyCallbackModeRegistrant != null) {
                riljLog("responseCallList: call ended, testing emergency call," +
                            " notify ECM Registrants");
                mEmergencyCallbackModeRegistrant.notifyRegistrant();
            }
        }
        return response;
        */
    }



    @Override
    protected Object
    responseSignalStrength(Parcel p) {
        return SignalStrength.makeSignalStrengthFromRilParcel(p);
    /*
        int gsmSignalStrength = p.readInt() & 0xff;
        int gsmBitErrorRate = p.readInt();
        int cdmaDbm = p.readInt();
        int cdmaEcio = p.readInt();
        int evdoDbm = p.readInt();
        int evdoEcio = p.readInt();
        int evdoSnr = p.readInt();
        int lteSignalStrength = p.readInt();
        int lteRsrp = p.readInt();
        int lteRsrq = p.readInt();
        int lteRssnr = p.readInt();
        int lteCqi = p.readInt();
        int tdScdmaRscp = p.readInt();
        // constructor sets default true, makeSignalStrengthFromRilParcel does not set it
        boolean isGsm = true;

        if ((lteSignalStrength & 0xff) == 255 || lteSignalStrength == 99) {
            lteSignalStrength = 99;
            lteRsrp = SignalStrength.INVALID;
            lteRsrq = SignalStrength.INVALID;
            lteRssnr = SignalStrength.INVALID;
            lteCqi = SignalStrength.INVALID;
        } else {
            lteSignalStrength &= 0xff;
        }

        if (RILJ_LOGD)
            riljLog("gsmSignalStrength:" + gsmSignalStrength + " gsmBitErrorRate:" + gsmBitErrorRate +
                    " cdmaDbm:" + cdmaDbm + " cdmaEcio:" + cdmaEcio + " evdoDbm:" + evdoDbm +
                    " evdoEcio: " + evdoEcio + " evdoSnr:" + evdoSnr +
                    " lteSignalStrength:" + lteSignalStrength + " lteRsrp:" + lteRsrp +
                    " lteRsrq:" + lteRsrq + " lteRssnr:" + lteRssnr + " lteCqi:" + lteCqi +
                    " tdScdmaRscp:" + tdScdmaRscp + " isGsm:" + (isGsm ? "true" : "false"));

        return new SignalStrength(gsmSignalStrength, gsmBitErrorRate, cdmaDbm, cdmaEcio, evdoDbm,
                evdoEcio, evdoSnr, lteSignalStrength, lteRsrp, lteRsrq, lteRssnr, lteCqi,
                tdScdmaRscp, isGsm);
                */
    }



    @Override
    protected void
    processUnsolicited (Parcel p) {
        Object ret;
        int dataPosition = p.dataPosition();
        int response = p.readInt();
        int newResponse = response;

        switch(response)
        {
            case 11001:
                //ret = responseSSReleaseCompleteNotification(p);
                //unsljLog(response);
                //if (this.mReleaseCompleteMessageRegistrant != null) {
                //    this.mReleaseCompleteMessageRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11002:
                ret = responseInts(p);
                unsljLogRet(response, ret);
                if (this.mCatSendSmsResultRegistrant != null) {
                    this.mCatSendSmsResultRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                    return;
                }
                return;
            case 11003:
                //ret = responseString(p);
                //if (this.mCatCallControlResultRegistrant != null) {
                //    this.mCatCallControlResultRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11008:
                //ret = responseVoid(p);
                //unsljLog(response);
                //if (this.mSmsDeviceReadyRegistrant != null) {
                //    this.mSmsDeviceReadyRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11009:
                ret = responseVoid(p);
                return;
            case 11010:
                //ret = responseString(p);
                //String str = ret;
                //Rlog.d(RILJ_LOG_TAG, "Executing Am " + str);
                //Am.main(str.split(" "));
                return;
            case 11013:
                //ret = responseRaw(p);
                //unsljLogRet(response, ret);
                //if (this.mSapRegistant != null) {
                //    this.mSapRegistant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11020:
                ret = responseRaw(p);
                return;
            case 11021:
                //ret = responseVoid(p);
                //unsljLogRet(response, ret);
                //if (this.mSimPbReadyRegistrant != null) {
                //    this.mSimPbReadyRegistrant.notifyRegistrant(new AsyncResult(null, null, null));
                //    return;
                //}
                return;
            case 11024:
                ret = responseRaw(p);
                return;
            case 11027:
                //ret = responseInts(p);
                //unsljLogvRet(response, ret);
                //if (this.mImsRegistrationStateChangedRegistrants != null) {
                //    this.mImsRegistrationStateChangedRegistrants.notifyRegistrants(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11028:
                //ret = responseCallModify(p);
                //unsljLogvRet(response, ret);
                //if (this.mModifyCallRegistrants != null) {
                //    this.mModifyCallRegistrants.notifyRegistrants(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11030:
                //ret = responseInts(p);
                //unsljLogRet(response, ret);
                //if (this.mCsFallbackRegistant != null) {
                //    this.mCsFallbackRegistant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11032:
                //ret = responseInts(p);
                //unsljLogvRet(response, ret);
                //if (this.mVoiceSystemIdRegistrant != null) {
                //    this.mVoiceSystemIdRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11034:
                //ret = responseVoid(p);
                //unsljLog(response);
                //Rlog.d(RILJ_LOG_TAG, "RIL_UNSOL_IMS_RETRYOVER");
                //if (this.mImsRegistrationRetryOver != null) {
                //    this.mImsRegistrationRetryOver.notifyRegistrants(new AsyncResult(null, null, null));
                //    return;
                //}
                return;
            case 11035:
                //ret = responseVoid(p);
                //unsljLogRet(response, ret);
                //if (this.mPbInitCompleteRegistrant != null) {
                //    this.mPbInitCompleteRegistrant.notifyRegistrant(new AsyncResult(null, null, null));
                //    return;
                //}
                return;
            case 11037:
                //ret = responseVoid(p);
                //unsljLogRet(response, ret);
                //if (this.mHysteresisDCNRegistant != null) {
                //    this.mHysteresisDCNRegistant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11043:
                //ret = responseVoid(p);
                //unsljLog(response);
                //if (this.mHomeNetworkRegistant != null) {
                //    this.mHomeNetworkRegistant.notifyRegistrant();
                //    return;
                //}
                return;
            case 11054:
                //ret = responseInts(p);
                //unsljLogRet(response, ret);
                //if (this.mStkSetupCallStatus != null) {
                //    this.mStkSetupCallStatus.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11056:
                ret = responseRaw(p);
                unsljLogRet(response, ret);
                Rlog.d(RILJ_LOG_TAG, "UNSOL_MODEM_CAPABILITY = mInstanceId" + this.mInstanceId);
                notifyModemCap((byte[]) ret, this.mInstanceId);
                return;
            case 11060:
                //ret = responseStrings(p);
                //unsljLogRet(response, ret);
                //if (this.mDunStateChangedRegistrant != null) {
                //}
                return;
            case 11061:
                //ret = responseInts(p);
                //unsljLogRet(response, ret);
                //if (this.mImsPrefNotiRegistrant != null) {
                //    this.mImsPrefNotiRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11062:
                //ret = responseInts(p);
                //unsljLogRet(response, ret);
                //if (this.mIccAppRefreshRegistrant != null) {
                //    this.mIccAppRefreshRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
            case 11064:
                //ret = responseString(p);
                //unsljLogRet(response, ret);
                //if (this.mSimIccIdNotiRegistrants != null) {
                //    this.mSimIccIdNotiRegistrants.notifyRegistrants(new AsyncResult(null, ret, null));
                //    return;
                //}
                return;
        }

        if (newResponse != response) {
            p.setDataPosition(dataPosition);
            p.writeInt(newResponse);
        }
        p.setDataPosition(dataPosition);
        super.processUnsolicited(p);
    }



    @Override
    public void
    acceptCall (Message result) {
        acceptCall(0, result);
    }

    public void
    acceptCall (int type, Message result) {
        RILRequest rr = RILRequest.obtain(40, result);
        riljLog(rr.serialString() + "> " + requestToString(rr.mRequest) + " " + type);
        rr.mParcel.writeInt(1);
        rr.mParcel.writeInt(type);
        send(rr);
    }

    public void dialEmergencyCall(String address, int clirMode, Message result) {
        RILRequest rr = RILRequest.obtain(10001, result);
        rr.mParcel.writeString(address);
        rr.mParcel.writeInt(clirMode);
        rr.mParcel.writeInt(0);
        rr.mParcel.writeInt(3);
        rr.mParcel.writeString("");
        rr.mParcel.writeInt(0);
        riljLog(rr.serialString() + "> " + requestToString(rr.mRequest));
        send(rr);
    }

    @Override
    protected RILRequest
    processSolicited (Parcel p)
    {
        int serial, error;
        boolean found = false;
        int dataPosition = p.dataPosition(); // save off position within the Parcel
        serial = p.readInt();
        error = p.readInt();
        RILRequest rr = null;

        /* Pre-process the reply before popping it */
        synchronized (mRequestList)
        {
            RILRequest tr = mRequestList.get(serial);
            if (tr != null && tr.mSerial == serial)
            {
                if (error == 0 || p.dataAvail() > 0)
                {
                    try
                    {
                        switch (tr.mRequest)
                        {
                            /*
                             * Get the request we're interested in !
                             */
                            case 10001: case 10002: case 10003: case 10004:
                            case 10005: case 10006: case 10007: case 10008:
                            case 10009: case 10010: case 10011: case 10012:
                            case 10013: case 10014: case 10015: case 10016:
                            case 10017: case 10018: case 10019: case 10020:
                            case 10021: case 10022: case 10023: case 10024:
                            case 10025: case 10026: case 10027: case 10028:
                                rr = tr; break;
                        }
                    }
                    catch (Throwable thr)
                    {
                        // Exceptions here usually mean invalid RIL responses
                        if (tr.mResult != null)
                        {
                            AsyncResult.forMessage(tr.mResult, null, thr);
                            tr.mResult.sendToTarget();
                        }
                        return tr;
                    }
                }
            }
        }

        if (rr == null)
        {
            /* Nothing we care about, go up */
            p.setDataPosition(dataPosition);
            // Forward responses that we are not overriding to the super class
            return super.processSolicited(p);
        }

        rr = findAndRemoveRequestFromList(serial);

        if (rr == null)
        {
            return rr;
        }

        Object ret = null;
        if (error == 0 || p.dataAvail() > 0)
        {
            /*
             * Process the requests we're interested in!
             */
            switch (rr.mRequest)
            {
                case 10001: ret = responseVoid(p); break;
                case 10002: ret = responseVoid(p); break;
                case 10003: ret = responseInts(p); break;
                case 10004: ret = responseVoid(p); break;
                case 10005: ret = responseVoid(p); break;
                case 10006: ret = responseVoid(p); break;
                case 10007: ret = responseVoid(p); break;
                //case 10008: ret = responseCbSettings(p); break;
                case 10009: ret = responseInts(p); break;
                //case 10010: ret = responseSIM_PB(p); break;
                case 10011: ret = responseInts(p); break;
                case 10012: ret = responseInts(p); break;
                //case 10013: ret = responseSIM_LockInfo(p); break;
                case 10014: ret = responseVoid(p); break;
                case 10015: ret = responseVoid(p); break;
                //case 10016: ret = responsePreferredNetworkList(p); break;
                case 10017: ret = responseInts(p); break;
                case 10018: ret = responseInts(p); break;
                case 10019: ret = responseVoid(p); break;
                case 10020: ret = responseSMS(p); break;
                case 10021: ret = responseVoid(p); break;
                case 10022: ret = responseVoid(p); break;
                //case 10023: ret = responseSimPowerDone(p); break;
                case 10024: ret = responseVoid(p); break;
                //case 10025: ret = responseBootstrap(p); break;
                //case 10026: ret = responseNaf(p); break;
                case 10027: ret = responseString(p); break;
                case 10028: ret = responseVoid(p); break;
                default:
                    throw new RuntimeException("Unrecognized solicited response: " + rr.mRequest);
            }
        }
        if (RILJ_LOGD) riljLog(rr.serialString() + "< " + requestToString(rr.mRequest)
                               + " " + retToString(rr.mRequest, ret));
        if (rr.mResult != null)
        {
            AsyncResult.forMessage(rr.mResult, ret, null);
            rr.mResult.sendToTarget();
        }
        return rr;
    }

    private Object
    responseDataRegistrationState(Parcel p) {
        String response[] = (String[])responseStrings(p);
        /* DANGER WILL ROBINSON
         * In some cases from Vodaphone we are receiving a RAT of 102
         * while in tunnels of the metro. Lets Assume that if we
         * receive 102 we actually want a RAT of 2 for EDGE service */
        if (response.length > 4 &&
            response[0].equals("1") &&
            response[3].equals("102")) {
            response[3] = "2";
        }
        return response;
    }
}
