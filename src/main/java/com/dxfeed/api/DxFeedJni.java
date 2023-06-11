package com.dxfeed.api;

import com.dxfeed.event.EventType;

import java.beans.PropertyChangeListener;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

public class DxFeedJni {
    static {
        String property = System.getProperty("com.devexperts.qd.impl.matrix.Agent.MaxBufferSize");
        System.out.println("[DxFeedJni]: After loading class " + DxFeedJni.class.getName() +
                ", com.devexperts.qd.impl.matrix.Agent.MaxBufferSize = " + property);
    }

    private static final ConcurrentHashMap<Long, PropertyChangeListener> changeListenerMap = new ConcurrentHashMap<>();
    private static final ConcurrentHashMap<Long, DXFeedEventListener<EventType<?>>> eventListenerMap = new ConcurrentHashMap<>();
    private static final AtomicLong nativeHandleId = new AtomicLong();

    // callbacks from native
    private static long newStateChangeEventListener(long userCallback, long userData) {
        long id = nativeHandleId.incrementAndGet();
        changeListenerMap.put(id, event -> nOnStateChangeListener(
                ((DXEndpoint.State) event.getOldValue()).ordinal(),
                ((DXEndpoint.State) event.getNewValue()).ordinal(),
                userCallback, userData));
        return id;
    }

    private static long newEventListener(long userCallback, long userData) {
        long id = nativeHandleId.incrementAndGet();
        eventListenerMap.put(id, eventList -> {
            EventsNative nativeTS = new EventsNative(eventList);
            nOnEventListener(eventList.size(), nativeTS.byteData(), nativeTS.doubleData(), nativeTS.pEventTypes,
                    userCallback, userData);
            nativeTS.clear();
        });
        return id;
    }

    private static void addStateChangeEventListener(DXEndpoint endpoint, long nativeHandleId) {
        PropertyChangeListener propertyChangeListener = changeListenerMap.get(nativeHandleId);
        if (propertyChangeListener != null) {
            System.out.println("addStateChangeEventListener, nativeHandle = " + nativeHandleId);
            endpoint.addStateChangeListener(propertyChangeListener);
        }
    }

    private static void addEventListener(DXFeedSubscription<EventType<?>> sub, long nativeHandleId) {
        DXFeedEventListener<EventType<?>> eventListener = eventListenerMap.get(nativeHandleId);
        if (eventListener != null) {
            System.out.println("addEventListener, nativeHandle = " + nativeHandleId);
            sub.addEventListener(eventListener);
        }
    }

    private static void removeStateChangeEventListener(DXEndpoint endpoint, long nativeHandleId) {
        PropertyChangeListener stateChangeListener = changeListenerMap.remove(nativeHandleId);
        if (stateChangeListener != null) {
            System.out.println("removeStateChangeEventListener, nativeHandle = " + nativeHandleId);
            endpoint.removeStateChangeListener(stateChangeListener);
        }
    }

    private static void removeEventListener(DXFeedSubscription<EventType<?>> sub, long nativeHandleId) {
        DXFeedEventListener<EventType<?>> eventListener = eventListenerMap.remove(nativeHandleId);
        if (eventListener != null) {
            System.out.println("removeEventListener, nativeHandle = " + nativeHandleId);
            sub.removeEventListener(eventListener);
        }
    }

    private static native void nOnStateChangeListener(int oldState, int newState, long userCallback, long userData);

    private static native void nOnEventListener(int size, byte[] byteData, double[] doubleData,
                                                byte[] pEventTypes, long userCallback, long userData);
}
