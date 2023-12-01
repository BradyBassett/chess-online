import styles from '../styles/page.module.scss';
import Board from './components/board';

export default function Home(): React.ReactElement {
  return (
    <main>
      <Board />
    </main>
  );
}
