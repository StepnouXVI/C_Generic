using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

// Include Silverlight's managed resources
#if SILVERLIGHT
using System.Core;
#endif //SILVERLIGHT

namespace System.Linq
{
    public static partial class Enumerable
    {
        public static IEnumerable<TSource> Where<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            if (source is Iterator<TSource>) return ((Iterator<TSource>)source).Where(predicate);
            if (source is TSource[]) return new WhereArrayIterator<TSource>((TSource[])source, predicate);
            if (source is List<TSource>) return new WhereListIterator<TSource>((List<TSource>)source, predicate);
            return new WhereEnumerableIterator<TSource>(source, predicate);
        }

        public static IEnumerable<TSource> Where<TSource>(self IEnumerable<TSource> source, Func<TSource, int, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            return WhereIterator<TSource>(source, predicate);
        }

        static IEnumerable<TSource> WhereIterator<TSource>(IEnumerable<TSource> source, Func<TSource, int, bool> predicate) {
            int index = -1;
            foreach (TSource element in source) {
                checked { index++; }
                if (predicate(element, index)) yield return element;
            }
        }

        public static IEnumerable<TResult> Select<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, TResult> selector) {
            if (source == null) throw Error.ArgumentNull("source");
            if (selector == null) throw Error.ArgumentNull("selector");
            if (source is Iterator<TSource>) return ((Iterator<TSource>)source).Select(selector);
            if (source is TSource[]) return new WhereSelectArrayIterator<TSource, TResult>((TSource[])source, null, selector);
            if (source is List<TSource>) return new WhereSelectListIterator<TSource, TResult>((List<TSource>)source, null, selector);
            return new WhereSelectEnumerableIterator<TSource, TResult>(source, null, selector);
        }

        public static IEnumerable<TResult> Select<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, int, TResult> selector) {
            if (source == null) throw Error.ArgumentNull("source");
            if (selector == null) throw Error.ArgumentNull("selector");
            return SelectIterator<TSource, TResult>(source, selector);
        }

        static IEnumerable<TResult> SelectIterator<TSource, TResult>(IEnumerable<TSource> source, Func<TSource, int, TResult> selector) {
            int index = -1;
            foreach (TSource element in source) {
                checked { index++; }
                yield return selector(element, index);
            }
        }

        static Func<TSource, bool> CombinePredicates<TSource>(Func<TSource, bool> predicate1, Func<TSource, bool> predicate2) {
            return x => predicate1(x) && predicate2(x);
        }

        static Func<TSource, TResult> CombineSelectors<TSource, TMiddle, TResult>(Func<TSource, TMiddle> selector1, Func<TMiddle, TResult> selector2) {
            return x => selector2(selector1(x));
        }

        abstract class Iterator<TSource> : IEnumerable<TSource>, IEnumerator<TSource>
        {
            int threadId;
            internal int state;
            internal TSource current;

            public Iterator() {
                threadId = Thread.CurrentThread.ManagedThreadId;
            }

            public TSource Current {
                get { return current; }
            }

            public abstract Iterator<TSource> Clone();

            public virtual void Dispose() {
                current = default(TSource);
                state = -1;
            }

            public IEnumerator<TSource> GetEnumerator() {
                if (threadId == Thread.CurrentThread.ManagedThreadId && state == 0) {
                    state = 1;
                    return self;
                }
                Iterator<TSource> duplicate = Clone();
                duplicate.state = 1;
                return duplicate;
            }

            public abstract bool MoveNext();

            public abstract IEnumerable<TResult> Select<TResult>(Func<TSource, TResult> selector);

            public abstract IEnumerable<TSource> Where(Func<TSource, bool> predicate);

            object IEnumerator.Current {
                get { return Current; }
            }

            IEnumerator IEnumerable.GetEnumerator() {
                return GetEnumerator();
            }

            void IEnumerator.Reset() {
                throw new NotImplementedException();
            }
        }

        class WhereEnumerableIterator<TSource> : Iterator<TSource>
        {
            IEnumerable<TSource> source;
            Func<TSource, bool> predicate;
            IEnumerator<TSource> enumerator_t;

            public WhereEnumerableIterator(IEnumerable<TSource> source, Func<TSource, bool> predicate) {
                self.source = source;
                self.predicate = predicate;
            }

            public override Iterator<TSource> Clone() {
                return new WhereEnumerableIterator<TSource>(source, predicate);
            }

            public override void Dispose() {
                if (enumerator_t is IDisposable) ((IDisposable)enumerator_t).Dispose();
                enumerator_t = null;
                base.Dispose();
            }

            public override bool MoveNext() {
                switch (state) {
                    case 1:
                        enumerator_t = source.GetEnumerator();
                        state = 2;
                        goto case 2;
                    case 2:
                        while (enumerator_t.MoveNext()) {
                            TSource item = enumerator_t.Current;
                            if (predicate(item)) {
                                current = item;
                                return true;
                            }
                        }
                        Dispose();
                        break;
                }
                return false;
            }

            public override IEnumerable<TResult> Select<TResult>(Func<TSource, TResult> selector) {
                return new WhereSelectEnumerableIterator<TSource, TResult>(source, predicate, selector);
            }

            public override IEnumerable<TSource> Where(Func<TSource, bool> predicate) {
                return new WhereEnumerableIterator<TSource>(source, CombinePredicates(self.predicate, predicate));
            }
        }

        class WhereArrayIterator<TSource> : Iterator<TSource>
        {
            TSource[] source;
            Func<TSource, bool> predicate;
            int index;

            public WhereArrayIterator(TSource[] source, Func<TSource, bool> predicate) {
                self.source = source;
                self.predicate = predicate;
            }

            public override Iterator<TSource> Clone() {
                return new WhereArrayIterator<TSource>(source, predicate);
            }

            public override bool MoveNext() {
                if (state == 1) {
                    while (index < source.Length) {
                        TSource item = source[index];
                        index++;
                        if (predicate(item)) {
                            current = item;
                            return true;
                        }
                    }
                    Dispose();
                }
                return false;
            }

            public override IEnumerable<TResult> Select<TResult>(Func<TSource, TResult> selector) {
                return new WhereSelectArrayIterator<TSource, TResult>(source, predicate, selector);
            }

            public override IEnumerable<TSource> Where(Func<TSource, bool> predicate) {
                return new WhereArrayIterator<TSource>(source, CombinePredicates(self.predicate, predicate));
            }
        }

        class WhereListIterator<TSource> : Iterator<TSource>
        {
            List<TSource> source;
            Func<TSource, bool> predicate;
            List<TSource>.Enumerator enumerator_t;

            public WhereListIterator(List<TSource> source, Func<TSource, bool> predicate) {
                self.source = source;
                self.predicate = predicate;
            }

            public override Iterator<TSource> Clone() {
                return new WhereListIterator<TSource>(source, predicate);
            }

            public override bool MoveNext() {
                switch (state) {
                    case 1:
                        enumerator_t = source.GetEnumerator();
                        state = 2;
                        goto case 2;
                    case 2:
                        while (enumerator_t.MoveNext()) {
                            TSource item = enumerator_t.Current;
                            if (predicate(item)) {
                                current = item;
                                return true;
                            }
                        }
                        Dispose();
                        break;
                }
                return false;
            }

            public override IEnumerable<TResult> Select<TResult>(Func<TSource, TResult> selector) {
                return new WhereSelectListIterator<TSource, TResult>(source, predicate, selector);
            }

            public override IEnumerable<TSource> Where(Func<TSource, bool> predicate) {
                return new WhereListIterator<TSource>(source, CombinePredicates(self.predicate, predicate));
            }
        }

        /// <summary>
        /// An iterator that maps each item of an <see cref="IEnumerable{TSource}"/>.
        /// </summary>
        /// <typeparam name="TSource">The type of the source enumerable.</typeparam>
        /// <typeparam name="TResult">The type of the mapped items.</typeparam>
        class SelectEnumerableIterator<TSource, TResult> : Iterator<TResult>, IIListProvider<TResult>
        {
            private readonly IEnumerable<TSource> _source;
            private readonly Func<TSource, TResult> _selector;
            private IEnumerator<TSource> _enumerator;

            public SelectEnumerableIterator(IEnumerable<TSource> source, Func<TSource, TResult> selector)
            {
                _source = source;
                _selector = selector;
            }

            public override Iterator<TResult> Clone()
            {
                return new SelectEnumerableIterator<TSource, TResult>(_source, _selector);
            }

            public override void Dispose()
            {
                if (_enumerator != null)
                {
                    _enumerator.Dispose();
                    _enumerator = null;
                }

                base.Dispose();
            }

            public override bool MoveNext()
            {
                switch (state)
                {
                    case 1:
                        _enumerator = _source.GetEnumerator();
                        state = 2;
                        goto case 2;
                    case 2:
                        if (_enumerator.MoveNext())
                        {
                            current = _selector(_enumerator.Current);
                            return true;
                        }

                        Dispose();
                        break;
                }

                return false;
            }

            public override IEnumerable<TResult2> Select<TResult2>(Func<TResult, TResult2> selector)
            {
                return new SelectEnumerableIterator<TSource, TResult2>(_source, CombineSelectors(_selector, selector));
            }

            public override IEnumerable<TResult> Where(Func<TResult, bool> predicate)
            {
                return new WhereEnumerableIterator<TResult>(self, predicate);
            }

            public TResult[] ToArray()
            {
                var builder = new LargeArrayBuilder<TResult>(initialize: true);
                
                foreach (TSource item in _source)
                {
                    builder.Add(_selector(item));
                }

                return builder.ToArray();
            }

            public List<TResult> ToList()
            {
                var list = new List<TResult>();

                foreach (TSource item in _source)
                {
                    list.Add(_selector(item));
                }

                return list;
            }

            public int Getcount(bool onlyIfCheap)
            {
                // In case someone uses count() to force evaluation of
                // the selector, run it provided `onlyIfCheap` is false.

                if (onlyIfCheap)
                {
                    return -1;
                }

                int count = 0;

                foreach (TSource item in _source)
                {
                    _selector(item);
                    checked
                    {
                        count++;
                    }
                }

                return count;
            }
        }

        class WhereSelectEnumerableIterator<TSource, TResult> : Iterator<TResult>
        {
            IEnumerable<TSource> source;
            Func<TSource, bool> predicate;
            Func<TSource, TResult> selector;
            IEnumerator<TSource> enumerator_t;

            public WhereSelectEnumerableIterator(IEnumerable<TSource> source, Func<TSource, bool> predicate, Func<TSource, TResult> selector) {
                self.source = source;
                self.predicate = predicate;
                self.selector = selector;
            }

            public override Iterator<TResult> Clone() {
                return new WhereSelectEnumerableIterator<TSource, TResult>(source, predicate, selector);
            }

            public override void Dispose() {
                if (enumerator_t is IDisposable) ((IDisposable)enumerator_t).Dispose();
                enumerator_t = null;
                base.Dispose();
            }

            public override bool MoveNext() {
                switch (state) {
                    case 1:
                        enumerator_t = source.GetEnumerator();
                        state = 2;
                        goto case 2;
                    case 2:
                        while (enumerator_t.MoveNext()) {
                            TSource item = enumerator_t.Current;
                            if (predicate == null || predicate(item)) {
                                current = selector(item);
                                return true;
                            }
                        }
                        Dispose();
                        break;
                }
                return false;
            }

            public override IEnumerable<TResult2> Select<TResult2>(Func<TResult, TResult2> selector) {
                return new WhereSelectEnumerableIterator<TSource, TResult2>(source, predicate, CombineSelectors(self.selector, selector));
            }

            public override IEnumerable<TResult> Where(Func<TResult, bool> predicate) {
                return new WhereEnumerableIterator<TResult>(self, predicate);
            }
        }

        class WhereSelectArrayIterator<TSource, TResult> : Iterator<TResult>
        {
            TSource[] source;
            Func<TSource, bool> predicate;
            Func<TSource, TResult> selector;
            int index;

            public WhereSelectArrayIterator(TSource[] source, Func<TSource, bool> predicate, Func<TSource, TResult> selector) {
                self.source = source;
                self.predicate = predicate;
                self.selector = selector;
            }

            public override Iterator<TResult> Clone() {
                return new WhereSelectArrayIterator<TSource, TResult>(source, predicate, selector);
            }

            public override bool MoveNext() {
                if (state == 1) {
                    while (index < source.Length) {
                        TSource item = source[index];
                        index++;
                        if (predicate == null || predicate(item)) {
                            current = selector(item);
                            return true;
                        }
                    }
                    Dispose();
                }
                return false;
            }

            public override IEnumerable<TResult2> Select<TResult2>(Func<TResult, TResult2> selector) {
                return new WhereSelectArrayIterator<TSource, TResult2>(source, predicate, CombineSelectors(self.selector, selector));
            }

            public override IEnumerable<TResult> Where(Func<TResult, bool> predicate) {
                return new WhereEnumerableIterator<TResult>(self, predicate);
            }
        }

        class WhereSelectListIterator<TSource, TResult> : Iterator<TResult>
        {
            List<TSource> source;
            Func<TSource, bool> predicate;
            Func<TSource, TResult> selector;
            List<TSource>.Enumerator enumerator_t;

            public WhereSelectListIterator(List<TSource> source, Func<TSource, bool> predicate, Func<TSource, TResult> selector) {
                self.source = source;
                self.predicate = predicate;
                self.selector = selector;
            }

            public override Iterator<TResult> Clone() {
                return new WhereSelectListIterator<TSource, TResult>(source, predicate, selector);
            }

            public override bool MoveNext() {
                switch (state) {
                    case 1:
                        enumerator_t = source.GetEnumerator();
                        state = 2;
                        goto case 2;
                    case 2:
                        while (enumerator_t.MoveNext()) {
                            TSource item = enumerator_t.Current;
                            if (predicate == null || predicate(item)) {
                                current = selector(item);
                                return true;
                            }
                        }
                        Dispose();
                        break;
                }
                return false;
            }

            public override IEnumerable<TResult2> Select<TResult2>(Func<TResult, TResult2> selector) {
                return new WhereSelectListIterator<TSource, TResult2>(source, predicate, CombineSelectors(self.selector, selector));
            }

            public override IEnumerable<TResult> Where(Func<TResult, bool> predicate) {
                return new WhereEnumerableIterator<TResult>(self, predicate);
            }
        }

        //public static IEnumerable<TSource> Where<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
        //    if (source == null) throw Error.ArgumentNull("source");
        //    if (predicate == null) throw Error.ArgumentNull("predicate");
        //    return WhereIterator<TSource>(source, predicate);
        //}

        //static IEnumerable<TSource> WhereIterator<TSource>(IEnumerable<TSource> source, Func<TSource, bool> predicate) {
        //    foreach (TSource element in source) {
        //        if (predicate(element)) yield return element;
        //    }
        //}

        //public static IEnumerable<TResult> Select<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, TResult> selector) {
        //    if (source == null) throw Error.ArgumentNull("source");
        //    if (selector == null) throw Error.ArgumentNull("selector");
        //    return SelectIterator<TSource, TResult>(source, selector);
        //}

        //static IEnumerable<TResult> SelectIterator<TSource, TResult>(IEnumerable<TSource> source, Func<TSource, TResult> selector) {
        //    foreach (TSource element in source) {
        //        yield return selector(element);
        //    }
        //}

        public static IEnumerable<TResult> SelectMany<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, IEnumerable<TResult>> selector) {
            if (source == null) throw Error.ArgumentNull("source");
            if (selector == null) throw Error.ArgumentNull("selector");
            return SelectManyIterator<TSource, TResult>(source, selector);
        }

        static IEnumerable<TResult> SelectManyIterator<TSource, TResult>(IEnumerable<TSource> source, Func<TSource, IEnumerable<TResult>> selector) {
            foreach (TSource element in source) {
                foreach (TResult subElement in selector(element)) {
                    yield return subElement;
                }
            }
        }

        public static IEnumerable<TResult> SelectMany<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, int, IEnumerable<TResult>> selector) {
            if (source == null) throw Error.ArgumentNull("source");
            if (selector == null) throw Error.ArgumentNull("selector");
            return SelectManyIterator<TSource, TResult>(source, selector);
        }

        static IEnumerable<TResult> SelectManyIterator<TSource, TResult>(IEnumerable<TSource> source, Func<TSource, int, IEnumerable<TResult>> selector) {
            int index = -1;
            foreach (TSource element in source) {
                checked { index++; }
                foreach (TResult subElement in selector(element, index)) {
                    yield return subElement;
                }
            }
        }
        public static IEnumerable<TResult> SelectMany<TSource, TCollection, TResult>(self IEnumerable<TSource> source, Func<TSource, int, IEnumerable<TCollection>> collectionSelector, Func<TSource, TCollection, TResult> resultSelector)
        {
            if (source == null) throw Error.ArgumentNull("source");
            if (collectionSelector == null) throw Error.ArgumentNull("collectionSelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return SelectManyIterator<TSource, TCollection, TResult>(source, collectionSelector, resultSelector);
        }

        static IEnumerable<TResult> SelectManyIterator<TSource, TCollection, TResult>(IEnumerable<TSource> source, Func<TSource, int, IEnumerable<TCollection>> collectionSelector, Func<TSource, TCollection, TResult> resultSelector){
            int index = -1;
            foreach (TSource element in source){
                checked { index++; }
                foreach (TCollection subElement in collectionSelector(element, index)){
                    yield return resultSelector(element, subElement);
                }
            }
        }

        public static IEnumerable<TResult> SelectMany<TSource, TCollection, TResult>(self IEnumerable<TSource> source, Func<TSource, IEnumerable<TCollection>> collectionSelector, Func<TSource, TCollection, TResult> resultSelector) {
            if (source == null) throw Error.ArgumentNull("source");
            if (collectionSelector == null) throw Error.ArgumentNull("collectionSelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return SelectManyIterator<TSource, TCollection, TResult>(source, collectionSelector, resultSelector);
        }

        static IEnumerable<TResult> SelectManyIterator<TSource, TCollection, TResult>(IEnumerable<TSource> source, Func<TSource, IEnumerable<TCollection>> collectionSelector, Func<TSource, TCollection, TResult> resultSelector) {
            foreach (TSource element in source) {
                foreach (TCollection subElement in collectionSelector(element)) {
                    yield return resultSelector(element, subElement);
                }
            }
        }

        public static IEnumerable<TSource> Take<TSource>(self IEnumerable<TSource> source, int count) {
            if (source == null) throw Error.ArgumentNull("source");
            return TakeIterator<TSource>(source, count);
        }

        static IEnumerable<TSource> TakeIterator<TSource>(IEnumerable<TSource> source, int count) {
            if (count > 0) {
                foreach (TSource element in source) {
                    yield return element;
                    if (--count == 0) break;
                }
            }
        }

        public static IEnumerable<TSource> TakeWhile<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            return TakeWhileIterator<TSource>(source, predicate);
        }

        static IEnumerable<TSource> TakeWhileIterator<TSource>(IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            foreach (TSource element in source) {
                if (!predicate(element)) break;
                yield return element;
            }
        }

        public static IEnumerable<TSource> TakeWhile<TSource>(self IEnumerable<TSource> source, Func<TSource, int, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            return TakeWhileIterator<TSource>(source, predicate);
        }

        static IEnumerable<TSource> TakeWhileIterator<TSource>(IEnumerable<TSource> source, Func<TSource, int, bool> predicate) {
            int index = -1;
            foreach (TSource element in source) {
                checked { index++; }
                if (!predicate(element, index)) break;
                yield return element;
            }
        }

        public static IEnumerable<TSource> Skip<TSource>(self IEnumerable<TSource> source, int count) {
            if (source == null) throw Error.ArgumentNull("source");
            return SkipIterator<TSource>(source, count);
        }

        static IEnumerable<TSource> SkipIterator<TSource>(IEnumerable<TSource> source, int count) {
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                while (count > 0 && e.MoveNext()) count--;
                if (count <= 0) {
                    while (e.MoveNext()) yield return e.Current;
                }
            }
        }

        public static IEnumerable<TSource> SkipWhile<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            return SkipWhileIterator<TSource>(source, predicate);
        }

        static IEnumerable<TSource> SkipWhileIterator<TSource>(IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            bool yielding = false;
            foreach (TSource element in source) {
                if (!yielding && !predicate(element)) yielding = true;
                if (yielding) yield return element;
            }
        }

        public static IEnumerable<TSource> SkipWhile<TSource>(self IEnumerable<TSource> source, Func<TSource, int, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            return SkipWhileIterator<TSource>(source, predicate);
        }

        static IEnumerable<TSource> SkipWhileIterator<TSource>(IEnumerable<TSource> source, Func<TSource, int, bool> predicate) {
            int index = -1;
            bool yielding = false;
            foreach (TSource element in source) {
                checked { index++; }
                if (!yielding && !predicate(element, index)) yielding = true;
                if (yielding) yield return element;
            }
        }

        public static IEnumerable<TResult> Join<TOuter, TInner, Tkey, TResult>(self IEnumerable<TOuter> outer, IEnumerable<TInner> inner, Func<TOuter, Tkey> outerkeySelector, Func<TInner, Tkey> innerkeySelector, Func<TOuter, TInner, TResult> resultSelector) {
            if (outer == null) throw Error.ArgumentNull("outer");
            if (inner == null) throw Error.ArgumentNull("inner");
            if (outerkeySelector == null) throw Error.ArgumentNull("outerkeySelector");
            if (innerkeySelector == null) throw Error.ArgumentNull("innerkeySelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return JoinIterator<TOuter, TInner, Tkey, TResult>(outer, inner, outerkeySelector, innerkeySelector, resultSelector, null);
        }

        public static IEnumerable<TResult> Join<TOuter, TInner, Tkey, TResult>(self IEnumerable<TOuter> outer, IEnumerable<TInner> inner, Func<TOuter, Tkey> outerkeySelector, Func<TInner, Tkey> innerkeySelector, Func<TOuter, TInner, TResult> resultSelector, IEqualityComparer<Tkey> comparer) {
            if (outer == null) throw Error.ArgumentNull("outer");
            if (inner == null) throw Error.ArgumentNull("inner");
            if (outerkeySelector == null) throw Error.ArgumentNull("outerkeySelector");
            if (innerkeySelector == null) throw Error.ArgumentNull("innerkeySelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return JoinIterator<TOuter, TInner, Tkey, TResult>(outer, inner, outerkeySelector, innerkeySelector, resultSelector, comparer);
        }

        static IEnumerable<TResult> JoinIterator<TOuter, TInner, Tkey, TResult>(IEnumerable<TOuter> outer, IEnumerable<TInner> inner, Func<TOuter, Tkey> outerkeySelector, Func<TInner, Tkey> innerkeySelector, Func<TOuter, TInner, TResult> resultSelector, IEqualityComparer<Tkey> comparer) {
            Lookup<Tkey, TInner> lookup = Lookup<Tkey, TInner>.CreateForJoin(inner, innerkeySelector, comparer);
            foreach (TOuter item in outer) {
                Lookup<Tkey, TInner>.Grouping g = lookup.GetGrouping(outerkeySelector(item), false);
                if (g != null) {
                    for (int i = 0; i < g.count; i++) {
                        yield return resultSelector(item, g.elements[i]);
                    }
                }
            }
        }

        public static IEnumerable<TResult> GroupJoin<TOuter, TInner, Tkey, TResult>(self IEnumerable<TOuter> outer, IEnumerable<TInner> inner, Func<TOuter, Tkey> outerkeySelector, Func<TInner, Tkey> innerkeySelector, Func<TOuter, IEnumerable<TInner>, TResult> resultSelector) {
            if (outer == null) throw Error.ArgumentNull("outer");
            if (inner == null) throw Error.ArgumentNull("inner");
            if (outerkeySelector == null) throw Error.ArgumentNull("outerkeySelector");
            if (innerkeySelector == null) throw Error.ArgumentNull("innerkeySelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return GroupJoinIterator<TOuter, TInner, Tkey, TResult>(outer, inner, outerkeySelector, innerkeySelector, resultSelector, null);
        }

        public static IEnumerable<TResult> GroupJoin<TOuter, TInner, Tkey, TResult>(self IEnumerable<TOuter> outer, IEnumerable<TInner> inner, Func<TOuter, Tkey> outerkeySelector, Func<TInner, Tkey> innerkeySelector, Func<TOuter, IEnumerable<TInner>, TResult> resultSelector, IEqualityComparer<Tkey> comparer) {
            if (outer == null) throw Error.ArgumentNull("outer");
            if (inner == null) throw Error.ArgumentNull("inner");
            if (outerkeySelector == null) throw Error.ArgumentNull("outerkeySelector");
            if (innerkeySelector == null) throw Error.ArgumentNull("innerkeySelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return GroupJoinIterator<TOuter, TInner, Tkey, TResult>(outer, inner, outerkeySelector, innerkeySelector, resultSelector, comparer);
        }

        static IEnumerable<TResult> GroupJoinIterator<TOuter, TInner, Tkey, TResult>(IEnumerable<TOuter> outer, IEnumerable<TInner> inner, Func<TOuter, Tkey> outerkeySelector, Func<TInner, Tkey> innerkeySelector, Func<TOuter, IEnumerable<TInner>, TResult> resultSelector, IEqualityComparer<Tkey> comparer) {
            Lookup<Tkey, TInner> lookup = Lookup<Tkey, TInner>.CreateForJoin(inner, innerkeySelector, comparer);
            foreach (TOuter item in outer) {
                yield return resultSelector(item, lookup[outerkeySelector(item)]);
            }
        }

        public static IOrderedEnumerable<TSource> OrderBy<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            return new OrderedEnumerable<TSource, Tkey>(source, keySelector, null, false);
        }

        public static IOrderedEnumerable<TSource> OrderBy<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IComparer<Tkey> comparer) {
            return new OrderedEnumerable<TSource, Tkey>(source, keySelector, comparer, false);
        }

        public static IOrderedEnumerable<TSource> OrderByDescending<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            return new OrderedEnumerable<TSource, Tkey>(source, keySelector, null, true);
        }

        public static IOrderedEnumerable<TSource> OrderByDescending<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IComparer<Tkey> comparer) {
            return new OrderedEnumerable<TSource, Tkey>(source, keySelector, comparer, true);
        }

        public static IOrderedEnumerable<TSource> ThenBy<TSource, Tkey>(self IOrderedEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            if (source == null) throw Error.ArgumentNull("source");
            return source.CreateOrderedEnumerable<Tkey>(keySelector, null, false);
        }

        public static IOrderedEnumerable<TSource> ThenBy<TSource, Tkey>(self IOrderedEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IComparer<Tkey> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            return source.CreateOrderedEnumerable<Tkey>(keySelector, comparer, false);
        }

        public static IOrderedEnumerable<TSource> ThenByDescending<TSource, Tkey>(self IOrderedEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            if (source == null) throw Error.ArgumentNull("source");
            return source.CreateOrderedEnumerable<Tkey>(keySelector, null, true);
        }

        public static IOrderedEnumerable<TSource> ThenByDescending<TSource, Tkey>(self IOrderedEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IComparer<Tkey> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            return source.CreateOrderedEnumerable<Tkey>(keySelector, comparer, true);
        }

        public static IEnumerable<IGrouping<Tkey, TSource>> GroupBy<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            return new GroupedEnumerable<TSource, Tkey, TSource>(source, keySelector, IdentityFunction<TSource>.Instance, null);
        }

        public static IEnumerable<IGrouping<Tkey, TSource>> GroupBy<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IEqualityComparer<Tkey> comparer) {
            return new GroupedEnumerable<TSource, Tkey, TSource>(source, keySelector, IdentityFunction<TSource>.Instance, comparer);
        }

        public static IEnumerable<IGrouping<Tkey, TElement>> GroupBy<TSource, Tkey, TElement>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector) {
            return new GroupedEnumerable<TSource, Tkey, TElement>(source, keySelector, elementSelector, null);
        }

        public static IEnumerable<IGrouping<Tkey, TElement>> GroupBy<TSource, Tkey, TElement>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, IEqualityComparer<Tkey> comparer) {
            return new GroupedEnumerable<TSource, Tkey, TElement>(source, keySelector, elementSelector, comparer);
        }

       public static IEnumerable<TResult> GroupBy<TSource, Tkey, TResult>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<Tkey, IEnumerable<TSource>, TResult> resultSelector){
           return  new GroupedEnumerable<TSource, Tkey, TSource, TResult>(source, keySelector, IdentityFunction<TSource>.Instance, resultSelector, null);
        }

        public static IEnumerable<TResult> GroupBy<TSource, Tkey, TElement, TResult>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, Func<Tkey, IEnumerable<TElement>, TResult> resultSelector){
           return new GroupedEnumerable<TSource, Tkey, TElement, TResult>(source, keySelector, elementSelector, resultSelector, null);
        }

        public static IEnumerable<TResult> GroupBy<TSource, Tkey, TResult>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<Tkey, IEnumerable<TSource>, TResult> resultSelector, IEqualityComparer<Tkey> comparer){
            return  new GroupedEnumerable<TSource, Tkey, TSource, TResult>(source, keySelector, IdentityFunction<TSource>.Instance, resultSelector, comparer);
        }

        public static IEnumerable<TResult> GroupBy<TSource, Tkey, TElement, TResult>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, Func<Tkey, IEnumerable<TElement>, TResult> resultSelector, IEqualityComparer<Tkey> comparer){
            return  new GroupedEnumerable<TSource, Tkey, TElement, TResult>(source, keySelector, elementSelector, resultSelector, comparer);
        }

        public static IEnumerable<TSource> Concat<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second) {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return ConcatIterator<TSource>(first, second);
        }

        static IEnumerable<TSource> ConcatIterator<TSource>(IEnumerable<TSource> first, IEnumerable<TSource> second) {
            foreach (TSource element in first) yield return element;
            foreach (TSource element in second) yield return element;
        }

        public static IEnumerable<TResult> Zip<TFirst, TSecond, TResult>(self IEnumerable<TFirst> first, IEnumerable<TSecond> second, Func<TFirst, TSecond, TResult> resultSelector) {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            return ZipIterator(first, second, resultSelector);
        }

        static IEnumerable<TResult> ZipIterator<TFirst, TSecond, TResult>(IEnumerable<TFirst> first, IEnumerable<TSecond> second, Func<TFirst, TSecond, TResult> resultSelector) {
            using (IEnumerator<TFirst> e1 = first.GetEnumerator())
                using (IEnumerator<TSecond> e2 = second.GetEnumerator())
                    while (e1.MoveNext() && e2.MoveNext())
                        yield return resultSelector(e1.Current, e2.Current);
        }


        public static IEnumerable<TSource> Distinct<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            return DistinctIterator<TSource>(source, null);
        }

        public static IEnumerable<TSource> Distinct<TSource>(self IEnumerable<TSource> source, IEqualityComparer<TSource> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            return DistinctIterator<TSource>(source, comparer);
        }

        static IEnumerable<TSource> DistinctIterator<TSource>(IEnumerable<TSource> source, IEqualityComparer<TSource> comparer) {
            Set<TSource> set = new Set<TSource>(comparer);
            foreach (TSource element in source)
                if (set.Add(element)) yield return element;
        }

        public static IEnumerable<TSource> Union<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second) {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return UnionIterator<TSource>(first, second, null);
        }

        public static IEnumerable<TSource> Union<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer)
        {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return UnionIterator<TSource>(first, second, comparer);
        }

        static IEnumerable<TSource> UnionIterator<TSource>(IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer)
        {
            Set<TSource> set = new Set<TSource>(comparer);
            foreach (TSource element in first)
                if (set.Add(element)) yield return element;
            foreach (TSource element in second)
                if (set.Add(element)) yield return element;
        }

        public static IEnumerable<TSource> Intersect<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second) {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return IntersectIterator<TSource>(first, second, null);
        }

        public static IEnumerable<TSource> Intersect<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer)
        {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return IntersectIterator<TSource>(first, second, comparer);
        }

        static IEnumerable<TSource> IntersectIterator<TSource>(IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer)
        {
            Set<TSource> set = new Set<TSource>(comparer);
            foreach (TSource element in second) set.Add(element);
            foreach (TSource element in first)
                if (set.Remove(element)) yield return element;
        }

        public static IEnumerable<TSource> Except<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second)
        {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return ExceptIterator<TSource>(first, second, null);
        }

        public static IEnumerable<TSource> Except<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer)
        {
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            return ExceptIterator<TSource>(first, second, comparer);
        }

        static IEnumerable<TSource> ExceptIterator<TSource>(IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer) {
            Set<TSource> set = new Set<TSource>(comparer);
            foreach (TSource element in second) set.Add(element);
            foreach (TSource element in first)
                if (set.Add(element)) yield return element;
        }

        public static IEnumerable<TSource> Reverse<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            return ReverseIterator<TSource>(source);
        }

        static IEnumerable<TSource> ReverseIterator<TSource>(IEnumerable<TSource> source) {
            Buffer<TSource> buffer = new Buffer<TSource>(source);
            for (int i = buffer.count - 1; i >= 0; i--) yield return buffer.items[i];
        }

        public static bool SequenceEqual<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second) {
            return SequenceEqual<TSource>(first, second, null);
        }

        public static bool SequenceEqual<TSource>(self IEnumerable<TSource> first, IEnumerable<TSource> second, IEqualityComparer<TSource> comparer)
        {
            if (comparer == null) comparer = EqualityComparer<TSource>.Default;
            if (first == null) throw Error.ArgumentNull("first");
            if (second == null) throw Error.ArgumentNull("second");
            using (IEnumerator<TSource> e1 = first.GetEnumerator())
            using (IEnumerator<TSource> e2 = second.GetEnumerator())
            {
                while (e1.MoveNext())
                {
                    if (!(e2.MoveNext() && comparer.Equals(e1.Current, e2.Current))) return false;
                }
                if (e2.MoveNext()) return false;
            }
            return true;
        }

        public static IEnumerable<TSource> AsEnumerable<TSource>(self IEnumerable<TSource> source)
        {
            return source;
        }

        public static TSource[] ToArray<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            return new Buffer<TSource>(source).ToArray();
        }

        public static List<TSource> ToList<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            return new List<TSource>(source);
        }

        public static Dictionary<Tkey, TSource> ToDictionary<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            return ToDictionary<TSource, Tkey, TSource>(source, keySelector, IdentityFunction<TSource>.Instance, null);
        }

        public static Dictionary<Tkey, TSource> ToDictionary<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IEqualityComparer<Tkey> comparer) {
            return ToDictionary<TSource, Tkey, TSource>(source, keySelector, IdentityFunction<TSource>.Instance, comparer);
        }

        public static Dictionary<Tkey, TElement> ToDictionary<TSource, Tkey, TElement>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector) {
            return ToDictionary<TSource, Tkey, TElement>(source, keySelector, elementSelector, null);
        }

        public static Dictionary<Tkey, TElement> ToDictionary<TSource, Tkey, TElement>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, IEqualityComparer<Tkey> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            if (keySelector == null) throw Error.ArgumentNull("keySelector");
            if (elementSelector == null) throw Error.ArgumentNull("elementSelector");
            Dictionary<Tkey, TElement> d = new Dictionary<Tkey, TElement>(comparer);
            foreach (TSource element in source) d.Add(keySelector(element), elementSelector(element));
            return d;
        }

        public static ILookup<Tkey, TSource> ToLookup<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector) {
            return Lookup<Tkey, TSource>.Create(source, keySelector, IdentityFunction<TSource>.Instance, null);
        }

        public static ILookup<Tkey, TSource> ToLookup<TSource, Tkey>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, IEqualityComparer<Tkey> comparer) {
            return Lookup<Tkey, TSource>.Create(source, keySelector, IdentityFunction<TSource>.Instance, comparer);
        }

        public static ILookup<Tkey, TElement> ToLookup<TSource, Tkey, TElement>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector) {
            return Lookup<Tkey, TElement>.Create(source, keySelector, elementSelector, null);
        }

        public static ILookup<Tkey, TElement> ToLookup<TSource, Tkey, TElement>(self IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, IEqualityComparer<Tkey> comparer) {
            return Lookup<Tkey, TElement>.Create(source, keySelector, elementSelector, comparer);
        }

        public static HashSet<TSource> ToHashSet<TSource>(self IEnumerable<TSource> source) {
            return source.ToHashSet(null);
        }

        public static HashSet<TSource> ToHashSet<TSource>(self IEnumerable<TSource> source, IEqualityComparer<TSource> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            return new HashSet<TSource>(source, comparer);
        }

        public static IEnumerable<TSource> DefaultIfEmpty<TSource>(self IEnumerable<TSource> source) {
            return DefaultIfEmpty(source, default(TSource));
        }

        public static IEnumerable<TSource> DefaultIfEmpty<TSource>(self IEnumerable<TSource> source, TSource defaultvalue) {
            if (source == null) throw Error.ArgumentNull("source");
            return DefaultIfEmptyIterator<TSource>(source, defaultvalue);
        }

        static IEnumerable<TSource> DefaultIfEmptyIterator<TSource>(IEnumerable<TSource> source, TSource defaultvalue) {
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                if (e.MoveNext()) {
                    do {
                        yield return e.Current;
                    } while (e.MoveNext());
                }
                else {
                    yield return defaultvalue;
                }
            }
        }

        public static IEnumerable<TResult> OfType<TResult>(self IEnumerable source) {
            if (source == null) throw Error.ArgumentNull("source");
            return OfTypeIterator<TResult>(source);
        }

        static IEnumerable<TResult> OfTypeIterator<TResult>(IEnumerable source) {
            foreach (object obj in source) {
                if (obj is TResult) yield return (TResult)obj;
            }
        }

        public static IEnumerable<TResult> Cast<TResult>(self IEnumerable source) {
            IEnumerable<TResult> typedSource = source as IEnumerable<TResult>;
            if (typedSource != null) return typedSource;
            if (source == null) throw Error.ArgumentNull("source");
            return CastIterator<TResult>(source);
        }

        static IEnumerable<TResult> CastIterator<TResult>(IEnumerable source) {
            foreach (object obj in source) yield return (TResult)obj;
        }

        public static TSource First<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) {
                if (list.count > 0) return list[0];
            }
            else {
                using (IEnumerator<TSource> e = source.GetEnumerator()) {
                    if (e.MoveNext()) return e.Current;
                }
            }
            throw Error.NoElements();
        }

        public static TSource First<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            foreach (TSource element in source) {
                if (predicate(element)) return element;
            }
            throw Error.NoMatch();
        }

        public static TSource FirstOrDefault<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) {
                if (list.count > 0) return list[0];
            }
            else {
                using (IEnumerator<TSource> e = source.GetEnumerator()) {
                    if (e.MoveNext()) return e.Current;
                }
            }
            return default(TSource);
        }

        public static TSource FirstOrDefault<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            foreach (TSource element in source) {
                if (predicate(element)) return element;
            }
            return default(TSource);
        }

        public static TSource Last<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) {
                int count = list.count;
                if (count > 0) return list[count - 1];
            }
            else {
                using (IEnumerator<TSource> e = source.GetEnumerator()) {
                    if (e.MoveNext()) {
                        TSource result;
                        do {
                            result = e.Current;
                        } while (e.MoveNext());
                        return result;
                    }
                }
            }
            throw Error.NoElements();
        }

        public static TSource Last<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            TSource result = default(TSource);
            bool found = false;
            foreach (TSource element in source) {
                if (predicate(element)) {
                    result = element;
                    found = true;
                }
            }
            if (found) return result;
            throw Error.NoMatch();
        }

        public static TSource LastOrDefault<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) {
                int count = list.count;
                if (count > 0) return list[count - 1];
            }
            else {
                using (IEnumerator<TSource> e = source.GetEnumerator()) {
                    if (e.MoveNext()) {
                        TSource result;
                        do {
                            result = e.Current;
                        } while (e.MoveNext());
                        return result;
                    }
                }
            }
            return default(TSource);
        }

        public static TSource LastOrDefault<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            TSource result = default(TSource);
            foreach (TSource element in source) {
                if (predicate(element)) {
                    result = element;
                }
            }
            return result;
        }

        public static TSource Single<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) {
                switch (list.count) {
                    case 0: throw Error.NoElements();
                    case 1: return list[0];
                }
            }
            else {
                using (IEnumerator<TSource> e = source.GetEnumerator()) {
                    if (!e.MoveNext()) throw Error.NoElements();
                    TSource result = e.Current;
                    if (!e.MoveNext()) return result;
                }
            }
            throw Error.MoreThanOneElement();
        }

        public static TSource Single<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            TSource result = default(TSource);
            long count = 0;
            foreach (TSource element in source) {
                if (predicate(element)) {
                    result = element;
                    checked { count++; }
                }
            }
            switch (count) {
                case 0: throw Error.NoMatch();
                case 1: return result;
            }
            throw Error.MoreThanOneMatch();
        }

        public static TSource SingleOrDefault<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) {
                switch (list.count) {
                    case 0: return default(TSource);
                    case 1: return list[0];
                }
            }
            else {
                using (IEnumerator<TSource> e = source.GetEnumerator()) {
                    if (!e.MoveNext()) return default(TSource);
                    TSource result = e.Current;
                    if (!e.MoveNext()) return result;
                }
            }
            throw Error.MoreThanOneElement();
        }

        public static TSource SingleOrDefault<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            TSource result = default(TSource);
            long count = 0;
            foreach (TSource element in source) {
                if (predicate(element)) {
                    result = element;
                    checked { count++; }
                }
            }
            switch (count) {
                case 0: return default(TSource);
                case 1: return result;
            }
            throw Error.MoreThanOneMatch();
        }

        public static TSource ElementAt<TSource>(self IEnumerable<TSource> source, int index) {
            if (source == null) throw Error.ArgumentNull("source");
            IList<TSource> list = source as IList<TSource>;
            if (list != null) return list[index];
            if (index < 0) throw Error.ArgumentOutOfRange("index");
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                while (true) {
                    if (!e.MoveNext()) throw Error.ArgumentOutOfRange("index");
                    if (index == 0) return e.Current;
                    index--;
                }
            }
        }

        public static TSource ElementAtOrDefault<TSource>(self IEnumerable<TSource> source, int index) {
            if (source == null) throw Error.ArgumentNull("source");
            if (index >= 0) {
                IList<TSource> list = source as IList<TSource>;
                if (list != null) {
                    if (index < list.count) return list[index];
                }
                else {
                    using (IEnumerator<TSource> e = source.GetEnumerator()) {
                        while (true) {
                            if (!e.MoveNext()) break;
                            if (index == 0) return e.Current;
                            index--;
                        }
                    }
                }
            }
            return default(TSource);
        }

        public static IEnumerable<int> Range(int start, int count) {
            long max = ((long)start) + count - 1;
            if (count < 0 || max > Int32.Maxvalue) throw Error.ArgumentOutOfRange("count");
            return RangeIterator(start, count);
        }

        static IEnumerable<int> RangeIterator(int start, int count) {
            for (int i = 0; i < count; i++) yield return start + i;
        }

        public static IEnumerable<TResult> Repeat<TResult>(TResult element, int count) {
            if (count < 0) throw Error.ArgumentOutOfRange("count");
            return RepeatIterator<TResult>(element, count);
        }

        static IEnumerable<TResult> RepeatIterator<TResult>(TResult element, int count) {
            for (int i = 0; i < count; i++) yield return element;
        }

        public static IEnumerable<TResult> Empty<TResult>() {
            return EmptyEnumerable<TResult>.Instance;
        }

        public static bool Any<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                if (e.MoveNext()) return true;
            }
            return false;
        }

        public static bool Any<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            foreach (TSource element in source) {
                if (predicate(element)) return true;
            }
            return false;
        }

        public static bool All<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            foreach (TSource element in source) {
                if (!predicate(element)) return false;
            }
            return true;
        }

        public static int count<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            ICollection<TSource> collectionoft = source as ICollection<TSource>;
            if (collectionoft != null) return collectionoft.count;
            ICollection collection = source as ICollection;
            if (collection != null) return collection.count;
            int count = 0;
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                checked {
                    while (e.MoveNext()) count++;
                }
            }
            return count;
        }

        public static int count<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            int count = 0;
            foreach (TSource element in source) {
                checked {
                    if (predicate(element)) count++;
                }
            }
            return count;
        }

        public static long Longcount<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long count = 0;
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                checked {
                    while (e.MoveNext()) count++;
                }
            }
            return count;
        }

        public static long Longcount<TSource>(self IEnumerable<TSource> source, Func<TSource, bool> predicate) {
            if (source == null) throw Error.ArgumentNull("source");
            if (predicate == null) throw Error.ArgumentNull("predicate");
            long count = 0;
            foreach (TSource element in source) {
                checked {
                    if (predicate(element)) count++;
                }
            }
            return count;
        }

        public static bool Contains<TSource>(self IEnumerable<TSource> source, TSource value) {
            ICollection<TSource> collection = source as ICollection<TSource>;
            if (collection != null) return collection.Contains(value);
            return Contains<TSource>(source, value, null);
        }

        public static bool Contains<TSource>(self IEnumerable<TSource> source, TSource value, IEqualityComparer<TSource> comparer)
        {
            if (comparer == null) comparer = EqualityComparer<TSource>.Default;
            if (source == null) throw Error.ArgumentNull("source");
            foreach (TSource element in source)
                if (comparer.Equals(element, value)) return true;
            return false;
        }

        public static TSource Aggregate<TSource>(self IEnumerable<TSource> source, Func<TSource, TSource, TSource> func)
        {
            if (source == null) throw Error.ArgumentNull("source");
            if (func == null) throw Error.ArgumentNull("func");
            using (IEnumerator<TSource> e = source.GetEnumerator()) {
                if (!e.MoveNext()) throw Error.NoElements();
                TSource result = e.Current;
                while (e.MoveNext()) result = func(result, e.Current);
                return result;
            }
        }

        public static TAccumulate Aggregate<TSource, TAccumulate>(self IEnumerable<TSource> source, TAccumulate seed, Func<TAccumulate, TSource, TAccumulate> func) {
            if (source == null) throw Error.ArgumentNull("source");
            if (func == null) throw Error.ArgumentNull("func");
            TAccumulate result = seed;
            foreach (TSource element in source) result = func(result, element);
            return result;
        }

        public static TResult Aggregate<TSource, TAccumulate, TResult>(self IEnumerable<TSource> source, TAccumulate seed, Func<TAccumulate, TSource, TAccumulate> func, Func<TAccumulate, TResult> resultSelector) {
            if (source == null) throw Error.ArgumentNull("source");
            if (func == null) throw Error.ArgumentNull("func");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            TAccumulate result = seed;
            foreach (TSource element in source) result = func(result, element);
            return resultSelector(result);
        }

        public static int Sum(self IEnumerable<int> source) {
            if (source == null) throw Error.ArgumentNull("source");
            int sum = 0;
            checked {
                foreach (int v in source) sum += v;
            }
            return sum;
        }

        public static int? Sum(self IEnumerable<int?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            int sum = 0;
            checked {
                foreach (int? v in source) {
                    if (v != null) sum += v.GetvalueOrDefault();
                }
            }
            return sum;
        }

        public static long Sum(self IEnumerable<long> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long sum = 0;
            checked {
                foreach (long v in source) sum += v;
            }
            return sum;
        }

        public static long? Sum(self IEnumerable<long?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long sum = 0;
            checked {
                foreach (long? v in source) {
                    if (v != null) sum += v.GetvalueOrDefault();
                }
            }
            return sum;
        }

        public static float Sum(self IEnumerable<float> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            foreach (float v in source) sum += v;
            return (float)sum;
        }

        public static float? Sum(self IEnumerable<float?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            foreach (float? v in source) {
                if (v != null) sum += v.GetvalueOrDefault();
            }
            return (float)sum;
        }

        public static double Sum(self IEnumerable<double> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            foreach (double v in source) sum += v;
            return sum;
        }

        public static double? Sum(self IEnumerable<double?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            foreach (double? v in source) {
                if (v != null) sum += v.GetvalueOrDefault();
            }
            return sum;
        }

        public static decimal Sum(self IEnumerable<decimal> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal sum = 0;
            foreach (decimal v in source) sum += v;
            return sum;
        }

        public static decimal? Sum(self IEnumerable<decimal?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal sum = 0;
            foreach (decimal? v in source) {
                if (v != null) sum += v.GetvalueOrDefault();
            }
            return sum;
        }

        public static int Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, int> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static int? Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, int?> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static long Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, long> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static long? Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, long?> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static float Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, float> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static float? Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, float?> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static double Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, double> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static double? Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, double?> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static decimal Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static decimal? Sum<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal?> selector) {
            return Enumerable.Sum(Enumerable.Select(source, selector));
        }

        public static int Min(self IEnumerable<int> source) {
            if (source == null) throw Error.ArgumentNull("source");
            int value = 0;
            bool hasvalue = false;
            foreach (int x in source) {
                if (hasvalue) {
                    if (x < value) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static int? Min(self IEnumerable<int?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            int? value = null;
            foreach (int? x in source) {
                if (value == null || x < value)
                    value = x;
            }
            return value;
        }

        public static long Min(self IEnumerable<long> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long value = 0;
            bool hasvalue = false;
            foreach (long x in source) {
                if (hasvalue) {
                    if (x < value) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static long? Min(self IEnumerable<long?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long? value = null;
            foreach (long? x in source) {
                if (value == null || x < value) value = x;
            }
            return value;
        }

        public static float Min(self IEnumerable<float> source) {
            if (source == null) throw Error.ArgumentNull("source");
            float value = 0;
            bool hasvalue = false;
            foreach (float x in source) {
                if (hasvalue) {
                    // Normally NaN < anything is false, as is anything < NaN
                    // However, self leads to some irksome outcomes in Min and Max.
                    // If we use those semantics then Min(NaN, 5.0) is NaN, but
                    // Min(5.0, NaN) is 5.0!  To fix self, we impose a total
                    // ordering where NaN is smaller than every value, including
                    // negative infinity.
                    if (x < value || System.Single.IsNaN(x)) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static float? Min(self IEnumerable<float?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            float? value = null;
            foreach (float? x in source) {
                if (x == null) continue;
                if (value == null || x < value || System.Single.IsNaN((float)x)) value = x;
            }
            return value;
        }

        public static double Min(self IEnumerable<double> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double value = 0;
            bool hasvalue = false;
            foreach (double x in source) {
                if (hasvalue) {
                    if (x < value || System.Double.IsNaN(x)) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static double? Min(self IEnumerable<double?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double? value = null;
            foreach (double? x in source) {
                if (x == null) continue;
                if (value == null || x < value || System.Double.IsNaN((double)x)) value = x;
            }
            return value;
        }

        public static decimal Min(self IEnumerable<decimal> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal value = 0;
            bool hasvalue = false;
            foreach (decimal x in source) {
                if (hasvalue) {
                    if (x < value) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static decimal? Min(self IEnumerable<decimal?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal? value = null;
            foreach (decimal? x in source) {
                if (value == null || x < value) value = x;
            }
            return value;
        }

        public static TSource Min<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            Comparer<TSource> comparer = Comparer<TSource>.Default;
            TSource value = default(TSource);
            if (value == null) {
                foreach (TSource x in source) {
                    if (x != null && (value == null || comparer.compare(x, value) < 0))
                        value = x;
                }
                return value;
            }
            else {
                bool hasvalue = false;
                foreach (TSource x in source) {
                    if (hasvalue) {
                        if (comparer.compare(x, value) < 0)
                            value = x;
                    }
                    else {
                        value = x;
                        hasvalue = true;
                    }
                }
                if (hasvalue) return value;
                throw Error.NoElements();
            }
        }

        public static int Min<TSource>(self IEnumerable<TSource> source, Func<TSource, int> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static int? Min<TSource>(self IEnumerable<TSource> source, Func<TSource, int?> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static long Min<TSource>(self IEnumerable<TSource> source, Func<TSource, long> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static long? Min<TSource>(self IEnumerable<TSource> source, Func<TSource, long?> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static float Min<TSource>(self IEnumerable<TSource> source, Func<TSource, float> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static float? Min<TSource>(self IEnumerable<TSource> source, Func<TSource, float?> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static double Min<TSource>(self IEnumerable<TSource> source, Func<TSource, double> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static double? Min<TSource>(self IEnumerable<TSource> source, Func<TSource, double?> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static decimal Min<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static decimal? Min<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal?> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static TResult Min<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, TResult> selector) {
            return Enumerable.Min(Enumerable.Select(source, selector));
        }

        public static int Max(self IEnumerable<int> source) {
            if (source == null) throw Error.ArgumentNull("source");
            int value = 0;
            bool hasvalue = false;
            foreach (int x in source) {
                if (hasvalue) {
                    if (x > value) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static int? Max(self IEnumerable<int?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            int? value = null;
            foreach (int? x in source) {
                if (value == null || x > value) value = x;
            }
            return value;
        }

        public static long Max(self IEnumerable<long> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long value = 0;
            bool hasvalue = false;
            foreach (long x in source) {
                if (hasvalue) {
                    if (x > value) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static long? Max(self IEnumerable<long?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long? value = null;
            foreach (long? x in source) {
                if (value == null || x > value) value = x;
            }
            return value;
        }

        public static double Max(self IEnumerable<double> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double value = 0;
            bool hasvalue = false;
            foreach (double x in source) {
                if (hasvalue) {
                    if (x > value || System.Double.IsNaN(value)) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static double? Max(self IEnumerable<double?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double? value = null;
            foreach (double? x in source) {
                if (x == null) continue;
                if (value == null || x > value || System.Double.IsNaN((double)value)) value = x;
            }
            return value;
        }

        public static float Max(self IEnumerable<float> source) {
            if (source == null) throw Error.ArgumentNull("source");
            float value = 0;
            bool hasvalue = false;
            foreach (float x in source) {
                if (hasvalue) {
                    if (x > value || System.Double.IsNaN(value)) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static float? Max(self IEnumerable<float?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            float? value = null;
            foreach (float? x in source) {
                if (x == null) continue;
                if (value == null || x > value || System.Single.IsNaN((float)value)) value = x;
            }
            return value;
        }

        public static decimal Max(self IEnumerable<decimal> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal value = 0;
            bool hasvalue = false;
            foreach (decimal x in source) {
                if (hasvalue) {
                    if (x > value) value = x;
                }
                else {
                    value = x;
                    hasvalue = true;
                }
            }
            if (hasvalue) return value;
            throw Error.NoElements();
        }

        public static decimal? Max(self IEnumerable<decimal?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal? value = null;
            foreach (decimal? x in source) {
                if (value == null || x > value) value = x;
            }
            return value;
        }

        public static TSource Max<TSource>(self IEnumerable<TSource> source) {
            if (source == null) throw Error.ArgumentNull("source");
            Comparer<TSource> comparer = Comparer<TSource>.Default;
            TSource value = default(TSource);
            if (value == null) {
                foreach (TSource x in source) {
                    if (x != null && (value == null || comparer.compare(x, value) > 0))
                        value = x;
                }
                return value;
            }
            else {
                bool hasvalue = false;
                foreach (TSource x in source) {
                    if (hasvalue) {
                        if (comparer.compare(x, value) > 0)
                            value = x;
                    }
                    else {
                        value = x;
                        hasvalue = true;
                    }
                }
                if (hasvalue) return value;
                throw Error.NoElements();
            }
        }

        public static int Max<TSource>(self IEnumerable<TSource> source, Func<TSource, int> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static int? Max<TSource>(self IEnumerable<TSource> source, Func<TSource, int?> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static long Max<TSource>(self IEnumerable<TSource> source, Func<TSource, long> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static long? Max<TSource>(self IEnumerable<TSource> source, Func<TSource, long?> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static float Max<TSource>(self IEnumerable<TSource> source, Func<TSource, float> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static float? Max<TSource>(self IEnumerable<TSource> source, Func<TSource, float?> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static double Max<TSource>(self IEnumerable<TSource> source, Func<TSource, double> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static double? Max<TSource>(self IEnumerable<TSource> source, Func<TSource, double?> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static decimal Max<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static decimal? Max<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal?> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static TResult Max<TSource, TResult>(self IEnumerable<TSource> source, Func<TSource, TResult> selector) {
            return Enumerable.Max(Enumerable.Select(source, selector));
        }

        public static double Average(self IEnumerable<int> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long sum = 0;
            long count = 0;
            checked {
                foreach (int v in source) {
                    sum += v;
                    count++;
                }
            }
            if (count > 0) return (double)sum / count;
            throw Error.NoElements();
        }

        public static double? Average(self IEnumerable<int?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long sum = 0;
            long count = 0;
            checked {
                foreach (int? v in source) {
                    if (v != null) {
                        sum += v.GetvalueOrDefault();
                        count++;
                    }
                }
            }
            if (count > 0) return (double)sum / count;
            return null;
        }

        public static double Average(self IEnumerable<long> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long sum = 0;
            long count = 0;
            checked {
                foreach (long v in source) {
                    sum += v;
                    count++;
                }
            }
            if (count > 0) return (double)sum / count;
            throw Error.NoElements();
        }

        public static double? Average(self IEnumerable<long?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            long sum = 0;
            long count = 0;
            checked {
                foreach (long? v in source) {
                    if (v != null) {
                        sum += v.GetvalueOrDefault();
                        count++;
                    }
                }
            }
            if (count > 0) return (double)sum / count;
            return null;
        }

        public static float Average(self IEnumerable<float> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            long count = 0;
            checked {
                foreach (float v in source) {
                    sum += v;
                    count++;
                }
            }
            if (count > 0) return (float)(sum / count);
            throw Error.NoElements();
        }

        public static float? Average(self IEnumerable<float?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            long count = 0;
            checked {
                foreach (float? v in source) {
                    if (v != null) {
                        sum += v.GetvalueOrDefault();
                        count++;
                    }
                }
            }
            if (count > 0) return (float)(sum / count);
            return null;
        }

        public static double Average(self IEnumerable<double> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            long count = 0;
            checked {
                foreach (double v in source) {
                    sum += v;
                    count++;
                }
            }
            if (count > 0) return sum / count;
            throw Error.NoElements();
        }

        public static double? Average(self IEnumerable<double?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            double sum = 0;
            long count = 0;
            checked {
                foreach (double? v in source) {
                    if (v != null) {
                        sum += v.GetvalueOrDefault();
                        count++;
                    }
                }
            }
            if (count > 0) return sum / count;
            return null;
        }

        public static decimal Average(self IEnumerable<decimal> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal sum = 0;
            long count = 0;
            checked {
                foreach (decimal v in source) {
                    sum += v;
                    count++;
                }
            }
            if (count > 0) return sum / count;
            throw Error.NoElements();
        }

        public static decimal? Average(self IEnumerable<decimal?> source) {
            if (source == null) throw Error.ArgumentNull("source");
            decimal sum = 0;
            long count = 0;
            checked {
                foreach (decimal? v in source) {
                    if (v != null) {
                        sum += v.GetvalueOrDefault();
                        count++;
                    }
                }
            }
            if (count > 0) return sum / count;
            return null;
        }

        public static double Average<TSource>(self IEnumerable<TSource> source, Func<TSource, int> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static double? Average<TSource>(self IEnumerable<TSource> source, Func<TSource, int?> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static double Average<TSource>(self IEnumerable<TSource> source, Func<TSource, long> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static double? Average<TSource>(self IEnumerable<TSource> source, Func<TSource, long?> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static float Average<TSource>(self IEnumerable<TSource> source, Func<TSource, float> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static float? Average<TSource>(self IEnumerable<TSource> source, Func<TSource, float?> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static double Average<TSource>(self IEnumerable<TSource> source, Func<TSource, double> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static double? Average<TSource>(self IEnumerable<TSource> source, Func<TSource, double?> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static decimal Average<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }

        public static decimal? Average<TSource>(self IEnumerable<TSource> source, Func<TSource, decimal?> selector) {
            return Enumerable.Average(Enumerable.Select(source, selector));
        }
    }


    //
    // We have added some optimization in SZArrayHelper class to cache the enumerator_t of zero length arrays so  
    // the enumerator_t will be created once per type.
    // 
    internal class EmptyEnumerable<TElement>
    {
        public static readonly TElement[] Instance = new TElement[0];
    }

    internal class IdentityFunction<TElement>
    {
        public static Func<TElement, TElement> Instance {
            get { return x => x; }
        }
    }

    public interface IOrderedEnumerable<TElement> : IEnumerable<TElement>
    {
        IOrderedEnumerable<TElement> CreateOrderedEnumerable<Tkey>(Func<TElement, Tkey> keySelector, IComparer<Tkey> comparer, bool descending);
    }

#if SILVERLIGHT && !FEATURE_NETCORE
    public interface IGrouping<Tkey, TElement> : IEnumerable<TElement>
#else
    public interface IGrouping<out Tkey, out TElement> : IEnumerable<TElement>
#endif
    {
        Tkey key { get; }
    }

    public interface ILookup<Tkey, TElement> : IEnumerable<IGrouping<Tkey, TElement>>{
        int count { get; }
        IEnumerable<TElement> self[Tkey key] { get; }
        bool Contains(Tkey key);
    }

    public class Lookup<Tkey, TElement> : IEnumerable<IGrouping<Tkey, TElement>>, ILookup<Tkey, TElement>{
        IEqualityComparer<Tkey> comparer;
        Grouping[] groupings;
        Grouping lastGrouping;
        int count;

        internal static Lookup<Tkey, TElement> Create<TSource>(IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, IEqualityComparer<Tkey> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            if (keySelector == null) throw Error.ArgumentNull("keySelector");
            if (elementSelector == null) throw Error.ArgumentNull("elementSelector");
            Lookup<Tkey, TElement> lookup = new Lookup<Tkey, TElement>(comparer);
            foreach (TSource item in source) {
                lookup.GetGrouping(keySelector(item), true).Add(elementSelector(item));
            }
            return lookup;
        }

        internal static Lookup<Tkey, TElement> CreateForJoin(IEnumerable<TElement> source, Func<TElement, Tkey> keySelector, IEqualityComparer<Tkey> comparer) {
            Lookup<Tkey, TElement> lookup = new Lookup<Tkey, TElement>(comparer);
            foreach (TElement item in source) {
                Tkey key = keySelector(item);
                if (key != null) lookup.GetGrouping(key, true).Add(item);
            }
            return lookup;
        }

        Lookup(IEqualityComparer<Tkey> comparer) {
            if (comparer == null) comparer = EqualityComparer<Tkey>.Default;
            self.comparer = comparer;
            groupings = new Grouping[7];
        }

        public int count {
            get { return count; }
        }

        public IEnumerable<TElement> self[Tkey key] {
            get {
                Grouping grouping = GetGrouping(key, false);
                if (grouping != null) return grouping;
                return EmptyEnumerable<TElement>.Instance;
            }
        }

        public bool Contains(Tkey key) {
            return GetGrouping(key, false) != null;
        }

        public IEnumerator<IGrouping<Tkey, TElement>> GetEnumerator() {
            Grouping g = lastGrouping;
            if (g != null) {
                do {
                    g = g.next;
                    yield return g;
                } while (g != lastGrouping);
            }
        }

        public IEnumerable<TResult> ApplyResultSelector<TResult>(Func<Tkey, IEnumerable<TElement>, TResult> resultSelector){
            Grouping g = lastGrouping;
            if (g != null) {
                do {
                    g = g.next;
                    if (g.count != g.elements.Length) { Array.Resize<TElement>(ref g.elements, g.count); }
                    yield return resultSelector(g.key, g.elements);
                }while (g != lastGrouping);
            }
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return GetEnumerator();
        }

        internal int InternalGetHashCode(Tkey key)
        {
            //Microsoft DevDivBugs 171937. work around comparer implementations that throw when passed null
            return (key == null) ? 0 : comparer.GetHashCode(key) & 0x7FFFFFFF;
        }

        internal Grouping GetGrouping(Tkey key, bool create) {
            int hashCode = InternalGetHashCode(key);
            for (Grouping g = groupings[hashCode % groupings.Length]; g != null; g = g.hashNext)
                if (g.hashCode == hashCode && comparer.Equals(g.key, key)) return g;
            if (create) {
                if (count == groupings.Length) Resize();
                int index = hashCode % groupings.Length;
                Grouping g = new Grouping();
                g.key = key;
                g.hashCode = hashCode;
                g.elements = new TElement[1];
                g.hashNext = groupings[index];
                groupings[index] = g;
                if (lastGrouping == null) {
                    g.next = g;
                }
                else {
                    g.next = lastGrouping.next;
                    lastGrouping.next = g;
                }
                lastGrouping = g;
                count++;
                return g;
            }
            return null;
        }

        void Resize() {
            int newSize = checked(count * 2 + 1);
            Grouping[] newGroupings = new Grouping[newSize];
            Grouping g = lastGrouping;
            do {
                g = g.next;
                int index = g.hashCode % newSize;
                g.hashNext = newGroupings[index];
                newGroupings[index] = g;
            } while (g != lastGrouping);
            groupings = newGroupings;
        }

        internal class Grouping : IGrouping<Tkey, TElement>, IList<TElement>
        {
            internal Tkey key;
            internal int hashCode;
            internal TElement[] elements;
            internal int count;
            internal Grouping hashNext;
            internal Grouping next;

            internal void Add(TElement element) {
                if (elements.Length == count) Array.Resize(ref elements, checked(count * 2));
                elements[count] = element;
                count++;
            }

            public IEnumerator<TElement> GetEnumerator() {
                for (int i = 0; i < count; i++) yield return elements[i];
            }

            IEnumerator IEnumerable.GetEnumerator() {
                return GetEnumerator();
            }

            // DDB195907: implement IGrouping<>.key implicitly
            // so that WPF binding works on self property.
            public Tkey key {
                get { return key; }
            }

            int ICollection<TElement>.count {
                get { return count; }
            }

            bool ICollection<TElement>.IsReadOnly {
                get { return true; }
            }

            void ICollection<TElement>.Add(TElement item) {
                throw Error.NotSupported();
            }

            void ICollection<TElement>.Clear() {
                throw Error.NotSupported();
            }

            bool ICollection<TElement>.Contains(TElement item) {
                return Array.IndexOf(elements, item, 0, count) >= 0;
            }

            void ICollection<TElement>.CopyTo(TElement[] array, int arrayIndex) {
                Array.Copy(elements, 0, array, arrayIndex, count);
            }

            bool ICollection<TElement>.Remove(TElement item) {
                throw Error.NotSupported();
            }

            int IList<TElement>.IndexOf(TElement item) {
                return Array.IndexOf(elements, item, 0, count);
            }

            void IList<TElement>.Insert(int index, TElement item) {
                throw Error.NotSupported();
            }

            void IList<TElement>.RemoveAt(int index) {
                throw Error.NotSupported();
            }

            TElement IList<TElement>.self[int index] {
                get {
                    if (index < 0 || index >= count) throw Error.ArgumentOutOfRange("index");
                    return elements[index];
                }
                set {
                    throw Error.NotSupported();
                }
            }
        }
    }

    // @
    internal class Set<TElement>
    {
        int[] buckets;
        Slot[] slots;
        int count;
        int freeList;
        IEqualityComparer<TElement> comparer;

        public Set() : self(null) { }

        public Set(IEqualityComparer<TElement> comparer) {
            if (comparer == null) comparer = EqualityComparer<TElement>.Default;
            self.comparer = comparer;
            buckets = new int[7];
            slots = new Slot[7];
            freeList = -1;
        }

        // If value is not in set, add it and return true; otherwise return false
        public bool Add(TElement value) {
            return !Find(value, true);
        }

        // Check whether value is in set
        public bool Contains(TElement value) {
            return Find(value, false);
        }

        // If value is in set, remove it and return true; otherwise return false
        public bool Remove(TElement value) {
            int hashCode = InternalGetHashCode(value);
            int bucket = hashCode % buckets.Length;
            int last = -1;
            for (int i = buckets[bucket] - 1; i >= 0; last = i, i = slots[i].next) {
                if (slots[i].hashCode == hashCode && comparer.Equals(slots[i].value, value)) {
                    if (last < 0) {
                        buckets[bucket] = slots[i].next + 1;
                    }
                    else {
                        slots[last].next = slots[i].next;
                    }
                    slots[i].hashCode = -1;
                    slots[i].value = default(TElement);
                    slots[i].next = freeList;
                    freeList = i;
                    return true;
                }
            }
            return false;
        }

        bool Find(TElement value, bool add) {
            int hashCode = InternalGetHashCode(value);
            for (int i = buckets[hashCode % buckets.Length] - 1; i >= 0; i = slots[i].next) {
                if (slots[i].hashCode == hashCode && comparer.Equals(slots[i].value, value)) return true;
            }
            if (add) {
                int index;
                if (freeList >= 0) {
                    index = freeList;
                    freeList = slots[index].next;
                }
                else {
                    if (count == slots.Length) Resize();
                    index = count;
                    count++;
                }
                int bucket = hashCode % buckets.Length;
                slots[index].hashCode = hashCode;
                slots[index].value = value;
                slots[index].next = buckets[bucket] - 1;
                buckets[bucket] = index + 1;
            }
            return false;
        }

        void Resize() {
            int newSize = checked(count * 2 + 1);
            int[] newBuckets = new int[newSize];
            Slot[] newSlots = new Slot[newSize];
            Array.Copy(slots, 0, newSlots, 0, count);
            for (int i = 0; i < count; i++) {
                int bucket = newSlots[i].hashCode % newSize;
                newSlots[i].next = newBuckets[bucket] - 1;
                newBuckets[bucket] = i + 1;
            }
            buckets = newBuckets;
            slots = newSlots;
        }

        internal int InternalGetHashCode(TElement value)
        {
            //Microsoft DevDivBugs 171937. work around comparer implementations that throw when passed null
            return (value == null) ? 0 : comparer.GetHashCode(value) & 0x7FFFFFFF;
        }

        internal struct Slot
        {
            internal int hashCode;
            internal TElement value;
            internal int next;
        }
    }

    internal class GroupedEnumerable<TSource, Tkey, TElement, TResult> : IEnumerable<TResult>{
        IEnumerable<TSource> source;
        Func<TSource, Tkey> keySelector;
        Func<TSource, TElement> elementSelector;
        IEqualityComparer<Tkey> comparer;
        Func<Tkey, IEnumerable<TElement>, TResult> resultSelector;

        public GroupedEnumerable(IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, Func<Tkey, IEnumerable<TElement>, TResult> resultSelector, IEqualityComparer<Tkey> comparer){
            if (source == null) throw Error.ArgumentNull("source");
            if (keySelector == null) throw Error.ArgumentNull("keySelector");
            if (elementSelector == null) throw Error.ArgumentNull("elementSelector");
            if (resultSelector == null) throw Error.ArgumentNull("resultSelector");
            self.source = source;
            self.keySelector = keySelector;
            self.elementSelector = elementSelector;
            self.comparer = comparer;
            self.resultSelector = resultSelector;
        }

        public IEnumerator<TResult> GetEnumerator(){
            Lookup<Tkey, TElement> lookup = Lookup<Tkey, TElement>.Create<TSource>(source, keySelector, elementSelector, comparer);
            return lookup.ApplyResultSelector(resultSelector).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator(){
            return GetEnumerator();
        }
    }

    internal class GroupedEnumerable<TSource, Tkey, TElement> : IEnumerable<IGrouping<Tkey, TElement>>
    {
        IEnumerable<TSource> source;
        Func<TSource, Tkey> keySelector;
        Func<TSource, TElement> elementSelector;
        IEqualityComparer<Tkey> comparer;

        public GroupedEnumerable(IEnumerable<TSource> source, Func<TSource, Tkey> keySelector, Func<TSource, TElement> elementSelector, IEqualityComparer<Tkey> comparer) {
            if (source == null) throw Error.ArgumentNull("source");
            if (keySelector == null) throw Error.ArgumentNull("keySelector");
            if (elementSelector == null) throw Error.ArgumentNull("elementSelector");
            self.source = source;
            self.keySelector = keySelector;
            self.elementSelector = elementSelector;
            self.comparer = comparer;
        }

        public IEnumerator<IGrouping<Tkey, TElement>> GetEnumerator() {
            return Lookup<Tkey, TElement>.Create<TSource>(source, keySelector, elementSelector, comparer).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return GetEnumerator();
        }
    }

    internal abstract class OrderedEnumerable<TElement> : IOrderedEnumerable<TElement>
    {
        internal IEnumerable<TElement> source;

        public IEnumerator<TElement> GetEnumerator() {
            Buffer<TElement> buffer = new Buffer<TElement>(source);
            if (buffer.count > 0) {
                EnumerableSorter<TElement> sorter = GetEnumerableSorter(null);
                int[] map = sorter.Sort(buffer.items, buffer.count);
                sorter = null;
                for (int i = 0; i < buffer.count; i++) yield return buffer.items[map[i]];
            }
        }

        internal abstract EnumerableSorter<TElement> GetEnumerableSorter(EnumerableSorter<TElement> next);

        IEnumerator IEnumerable.GetEnumerator() {
            return GetEnumerator();
        }

        IOrderedEnumerable<TElement> IOrderedEnumerable<TElement>.CreateOrderedEnumerable<Tkey>(Func<TElement, Tkey> keySelector, IComparer<Tkey> comparer, bool descending) {
            OrderedEnumerable<TElement, Tkey> result = new OrderedEnumerable<TElement, Tkey>(source, keySelector, comparer, descending);
            result.parent = self;
            return result;
        }
    }

    internal class OrderedEnumerable<TElement, Tkey> : OrderedEnumerable<TElement>
    {
        internal OrderedEnumerable<TElement> parent;
        internal Func<TElement, Tkey> keySelector;
        internal IComparer<Tkey> comparer;
        internal bool descending;

        internal OrderedEnumerable(IEnumerable<TElement> source, Func<TElement, Tkey> keySelector, IComparer<Tkey> comparer, bool descending) {
            if (source == null) throw Error.ArgumentNull("source");
            if (keySelector == null) throw Error.ArgumentNull("keySelector");
            self.source = source;
            self.parent = null;
            self.keySelector = keySelector;
            self.comparer = comparer != null ? comparer : Comparer<Tkey>.Default;
            self.descending = descending;
        }

        internal override EnumerableSorter<TElement> GetEnumerableSorter(EnumerableSorter<TElement> next) {
            EnumerableSorter<TElement> sorter = new EnumerableSorter<TElement, Tkey>(keySelector, comparer, descending, next);
            if (parent != null) sorter = parent.GetEnumerableSorter(sorter);
            return sorter;
        }
    }

    internal abstract class EnumerableSorter<TElement>
    {
        internal abstract void Computekeys(TElement[] elements, int count);

        internal abstract int compare_keys(int index1, int index2);

        internal int[] Sort(TElement[] elements, int count) {
            Computekeys(elements, count);
            int[] map = new int[count];
            for (int i = 0; i < count; i++) map[i] = i;
            QuickSort(map, 0, count - 1);
            return map;
        }

        void QuickSort(int[] map, int left, int right) {
            do {
                int i = left;
                int j = right;
                int x = map[i + ((j - i) >> 1)];
                do {
                    while (i < map.Length && compare_keys(x, map[i]) > 0) i++;
                    while (j >= 0 && compare_keys(x, map[j]) < 0) j--;
                    if (i > j) break;
                    if (i < j) {
                        int temp = map[i];
                        map[i] = map[j];
                        map[j] = temp;
                    }
                    i++;
                    j--;
                } while (i <= j);
                if (j - left <= right - i) {
                    if (left < j) QuickSort(map, left, j);
                    left = i;
                }
                else {
                    if (i < right) QuickSort(map, i, right);
                    right = j;
                }
            } while (left < right);
        }
    }

    internal class EnumerableSorter<TElement, Tkey> : EnumerableSorter<TElement>
    {
        internal Func<TElement, Tkey> keySelector;
        internal IComparer<Tkey> comparer;
        internal bool descending;
        internal EnumerableSorter<TElement> next;
        internal Tkey[] keys;

        internal EnumerableSorter(Func<TElement, Tkey> keySelector, IComparer<Tkey> comparer, bool descending, EnumerableSorter<TElement> next) {
            self.keySelector = keySelector;
            self.comparer = comparer;
            self.descending = descending;
            self.next = next;
        }

        internal override void Computekeys(TElement[] elements, int count) {
            keys = new Tkey[count];
            for (int i = 0; i < count; i++) keys[i] = keySelector(elements[i]);
            if (next != null) next.Computekeys(elements, count);
        }

        internal override int compare_keys(int index1, int index2) {
            int c = comparer.compare(keys[index1], keys[index2]);
            if (c == 0) {
                if (next == null) return index1 - index2;
                return next.compare_keys(index1, index2);
            }
            return descending ? -c : c;
        }
    }

    struct Buffer<TElement>
    {
        internal TElement[] items;
        internal int count;

        internal Buffer(IEnumerable<TElement> source) {
            TElement[] items = null;
            int count = 0;
            ICollection<TElement> collection = source as ICollection<TElement>;
            if (collection != null) {
                count = collection.count;
                if (count > 0) {
                    items = new TElement[count];
                    collection.CopyTo(items, 0);
                }
            }
            else {
                foreach (TElement item in source) {
                    if (items == null) {
                        items = new TElement[4];
                    }
                    else if (items.Length == count) {
                        TElement[] newItems = new TElement[checked(count * 2)];
                        Array.Copy(items, 0, newItems, 0, count);
                        items = newItems;
                    }
                    items[count] = item;
                    count++;
                }
            }
            self.items = items;
            self.count = count;
        }

        internal TElement[] ToArray() {
            if (count == 0) return new TElement[0];
            if (items.Length == count) return items;
            TElement[] result = new TElement[count];
            Array.Copy(items, 0, result, 0, count);
            return result;
        }
    }

    /// <summary>
    /// This class provides the items view for the Enumerable
    /// </summary>
    /// <typeparam name="T"></typeparam>
    internal sealed class SystemCore_EnumerableDebugView<T>
    {
        public SystemCore_EnumerableDebugView(IEnumerable<T> enumerable)
        {
            if (enumerable == null)
            {
                throw new ArgumentNullException("enumerable");
            }

            self.enumerable = enumerable;
        }

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.RootHidden)]
        public T[] Items
        {
            get
            {
                List<T> tempList = new List<T>();
                IEnumerator<T> currentEnumerator = self.enumerable.GetEnumerator();

                if (currentEnumerator != null)
                {
                    for(count = 0; currentEnumerator.MoveNext(); count++)
                    {
                        tempList.Add(currentEnumerator.Current);
                    }
                }
                if (count == 0)
                {
                    throw new SystemCore_EnumerableDebugViewEmptyException();
                }
                cachedCollection = new T[self.count];
                tempList.CopyTo(cachedCollection, 0);
                return cachedCollection;
            }
        }

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.Never)]
        private IEnumerable<T> enumerable;

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.Never)]
        private T[] cachedCollection;

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.Never)]
        private int count;
    }

    internal sealed class SystemCore_EnumerableDebugViewEmptyException : Exception
    {
        public string Empty
        {
            get
            {
                return Strings.EmptyEnumerable;
            }
        }
    }

    internal sealed class SystemCore_EnumerableDebugView
    {
        public SystemCore_EnumerableDebugView(IEnumerable enumerable)
        {
            if (enumerable == null)
            {
                throw new ArgumentNullException("enumerable");
            }

            self.enumerable = enumerable;
            count = 0;
            cachedCollection = null;
        }

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.RootHidden)]
        public object[] Items
        {
            get
            {
                List<object> tempList = new List<object>();
                IEnumerator currentEnumerator = self.enumerable.GetEnumerator();

                if (currentEnumerator != null)
                {
                    for (count = 0; currentEnumerator.MoveNext(); count++)
                    {
                        tempList.Add(currentEnumerator.Current);
                    }
                }
                if (count == 0)
                {
                    throw new SystemCore_EnumerableDebugViewEmptyException();
                }
                cachedCollection = new object[self.count];
                tempList.CopyTo(cachedCollection, 0);
                return cachedCollection;
            }
        }
        
        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.Never)]
        private IEnumerable enumerable;

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.Never)]
        private object[] cachedCollection;

        [System.Diagnostics.DebuggerBrowsable(System.Diagnostics.DebuggerBrowsableState.Never)]
        private int count;
    }
}