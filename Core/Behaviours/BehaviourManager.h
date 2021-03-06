/*
	This file is part of the MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef MINSG_BEHAVIOURMANAGER_H
#define MINSG_BEHAVIOURMANAGER_H

#include "AbstractBehaviour.h"
#include <Util/ReferenceCounter.h>
#include <map>
#include <list>
#include <vector>

namespace MinSG{

/**
 * BehaviourManager
 * Class to collect and organize Behaviours
 */
class BehaviourManager : public Util::ReferenceCounter<BehaviourManager> {
	PROVIDES_TYPE_NAME_NV(BehaviourManager)

	public:
		//! (ctor)
		BehaviourManager();

		//! (dtor)
		~BehaviourManager();

		/**
		 * @name Registered Behaviours (deprecated)
		 */
		//@{
	public:
		typedef std::list<Util::Reference<AbstractBehaviour> > behaviourList_t;
		typedef std::list<Util::Reference<AbstractNodeBehaviour> > nodeBehaviourList_t;
		typedef std::list<Util::Reference<AbstractStateBehaviour> > stateBehaviourList_t;
		typedef std::multimap<Node *,Util::Reference<AbstractNodeBehaviour> > nodeBehaviourRegistry_t;
		typedef std::multimap<State *,Util::Reference<AbstractStateBehaviour> > stateBehaviourRegistry_t;

		void registerBehaviour(AbstractBehaviour * behavior);
		void removeBehaviour(AbstractBehaviour * behaviour);
		void clearBehaviours();
		void executeBehaviours(Behavior::timestamp_t timeSec);
		void executeBehaviours(Behavior::timestamp_t timeSec,behaviourList_t & finishedBehaviours);

		nodeBehaviourList_t getBehavioursByNode(Node * node)const;
		stateBehaviourList_t getBehavioursByState(State * state)const;

	private:
		nodeBehaviourRegistry_t registeredNodeBehaviours;
		stateBehaviourRegistry_t registeredStateBehaviours;
		//@}
		
		
	// -----------------------------------------------------------------------------------------	

		/**
		 * @name Behaviors II
		 */
		//@{
				
	private:
		// id 
		Util::StringIdentifier attrName_behaviorStore;
		std::vector<Util::Reference<BehaviorStatus>> activeBehaviorStatuses;

		void executeBehaviors(Behavior::timestamp_t timeSec); // called by executeBehaviours
	 public:
		BehaviorStatus * startNodeBehavior(Behavior *, Node *);
		BehaviorStatus * startStateBehavior(Behavior *, State *);
		std::vector<BehaviorStatus*> getActiveBehaviorStatusesByNode(Node *);
		std::vector<BehaviorStatus*> getActiveBehaviorStatusesByState(State *);
		const std::vector<Util::Reference<BehaviorStatus>> & getActiveBehaviorStatuses()const{	return activeBehaviorStatuses;	}
		//@}
		
};
}
#endif // MINSG_BEHAVIOURMANAGER_H
