package com.dxfeed.api;

// https://github.com/dxFeed/dxfeed-graal-native-sdk/blob/main/src/main/c/api/dxfg_events.h#LL75C30-L75C30
public enum DxfgEventClazzT {
    DXFG_EVENT_QUOTE,      // LASTING
    DXFG_EVENT_PROFILE,        // LASTING
    DXFG_EVENT_SUMMARY,        // LASTING
    DXFG_EVENT_GREEKS,         // LASTING + INDEXED -> TIME_SERIES
    DXFG_EVENT_CANDLE,         // LASTING + INDEXED -> TIME_SERIES
    DXFG_EVENT_DAILY_CANDLE,   // LASTING + INDEXED -> TIME_SERIES -> CANDLE
    DXFG_EVENT_UNDERLYING,     // LASTING + INDEXED -> TIME_SERIES
    DXFG_EVENT_THEO_PRICE,     // LASTING + INDEXED -> TIME_SERIES
    // abstract DXFG_EVENT_TRADE_BASE,     // LASTING
    DXFG_EVENT_TRADE,          // LASTING -> TRADE_BASE
    DXFG_EVENT_TRADE_ETH,      // LASTING -> TRADE_BASE
    DXFG_EVENT_CONFIGURATION,  // LASTING
    DXFG_EVENT_MESSAGE,        //
    DXFG_EVENT_TIME_AND_SALE,  // INDEXED -> TIME_SERIES
    DXFG_EVENT_ORDER_BASE,     // INDEXED
    DXFG_EVENT_ORDER,          // INDEXED -> ORDER_BASE
    DXFG_EVENT_ANALYTIC_ORDER, // INDEXED -> ORDER_BASE -> ORDER
    DXFG_EVENT_SPREAD_ORDER,   // INDEXED -> ORDER_BASE
    DXFG_EVENT_SERIES,         // INDEXED
    DXFG_EVENT_OPTION_SALE;    // INDEXED


    public byte eventOrdinal() {
        return (byte) this.ordinal();
    }
}
