/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007 Ferdinando Ametrano
 Copyright (C) 2005 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/instruments/bonds/zerocouponbond.hpp>
#include <ql/cashflows/simplecashflow.hpp>

namespace QuantLib {

    ZeroCouponBond::ZeroCouponBond(Natural settlementDays,
                                   const Calendar& calendar,
                                   Real faceAmount,
                                   const Date& maturityDate,
                                   BusinessDayConvention paymentConvention,
                                   Real redemption,
                                   const Date& issueDate)
    : Bond(settlementDays, calendar, faceAmount, issueDate) {

        //firstAccrualDate_= Null<Date>(); // redundant for the sake of clarity
        maturityDate_    = maturityDate;

        Date redemptionDate = calendar_.adjust(maturityDate_,
                                               paymentConvention);
        cashflows_ = Leg(1, boost::shared_ptr<CashFlow>(new
            SimpleCashFlow(faceAmount_*redemption/100, redemptionDate)));

        QL_ENSURE(!cashflows().empty(), "bond with no cashflows!");
    }

}
